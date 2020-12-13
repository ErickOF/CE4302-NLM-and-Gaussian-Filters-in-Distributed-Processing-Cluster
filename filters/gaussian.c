#include <stdint.h>
#include <stdio.h>
#include <sys/param.h>

#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libs/stb/stb_image_write.h"


void rgb2gray(uint8_t* img, uint8_t* gray_ptr, int img_size)
{
    uint8_t* img_ptr = img;

    while (img_ptr != img + img_size)
    {
        // Convert RGB pixel to gray
        *gray_ptr = (uint8_t)(0.3*(*img_ptr) + 0.59*(*(img_ptr + 1)) + 0.11*(*(img_ptr + 2)));

        // Next pixel
        img_ptr += 3;
        gray_ptr++;
    }
}

void get_window(uint8_t* img, uint8_t* window, int i, int j, int height, int size)
{
    int mid = (int) (size - 1)/2;

    for (int m = -mid; m < mid + 1; m++)
    {
        for (int n = -mid; n < mid + 1; n++)
        {
            *(window) = *(img + (i*height + m) + j + n);
            window++;
        }
    }
}

void get_gaussian_kernel(double* kernel, int size, double stdev)
{
    double sum = 0;
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            double x = i - (size - 1) / 2.0;
            double y = j - (size - 1) / 2.0;

            kernel[i*size + j] = exp(-(x*x + y*y)/(2*stdev*stdev));
            sum += kernel[i*size + j];
        }
    }

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            kernel[i*size + j] /= sum;
        }

        printf("\n");
    }
}

void gaussian_filter(uint8_t* img, uint8_t* filtered, int width, int height, int window_size, double stdev)
{
    int mid_window = (int) (window_size - 1)/2;

    uint8_t* window = (uint8_t*) calloc(window_size * window_size, sizeof(uint8_t));
    double* gaussian_kernel = (double*) calloc(window_size * window_size, sizeof(double));

    get_gaussian_kernel(gaussian_kernel, window_size, stdev);

    for (int i = window_size; i < width - window_size; i++)
    {
        for (int j = window_size; j < height - window_size; j++)
        {
            double sum = 0.0;

            get_window(img, window, i, j, height, window_size);

            // Compare window against the similarity window
            for (int u = 0; u < window_size; u++)
            {
                for (int v = 0; v < window_size; v++)
                {
                    sum += gaussian_kernel[u*window_size + v]*((double) window[u*window_size + v]);
                }
            }

            uint8_t value = 0;

            if (sum > 255)
            {
                value = 255;
            } else if (sum > 0)
            {
                value = (uint8_t) sum;
            }

            filtered[i*height + j] = value;
        }
    }

    // Free memory
    free(window);
    free(gaussian_kernel);
}


int main(int argc, char* argv[])
{
    printf("\n");

    if (argc < 4)
    {
        printf("Args were not provided. make nlm w=3 sigma=2 imgs=\"img1 img2 img3 etc\".\n");
    }
    else
    {
        int win_size = atoi(argv[1]);
        float sigma = atof(argv[2]);

        for (int i = 3; i < argc; i++)
        {
            int width, height, channels;

            // Load image
            uint8_t* rgb_img = stbi_load(argv[i], &width, &height, &channels, 3);

            if (rgb_img == NULL)
            {
                printf("Error loading the image in %s.\n", argv[i]);
                continue;
            }

            // Convert image to gray
            size_t img_size = width * height * channels;
            size_t gray_img_size = width * height;

            uint8_t* gray_img = (uint8_t*) calloc(gray_img_size, sizeof(uint8_t));

            if (gray_img == NULL)
            {
                printf("Unable to allocate memory for the gray image.\n");
                exit(1);
            }

            rgb2gray(rgb_img, gray_img, img_size);

            // Allocate memory for the filtered image
            uint8_t* filtered_img = (uint8_t*) calloc(gray_img_size, sizeof(uint8_t));

            if (filtered_img == NULL)
            {
                printf("Unable to allocate memory for the filtered image.\n");
                exit(1);
            }

            // Gaussian filter
            gaussian_filter(gray_img, filtered_img, width, height, win_size, sigma);

            char output[26];
            sprintf(output, "%s%d%s", "outputs/gaussian", i - 3, ".jpg");

            // Save image
            stbi_write_jpg(output, width, height, 1, filtered_img, width);

            // Free memory
            stbi_image_free(rgb_img);
            stbi_image_free(gray_img);
            stbi_image_free(filtered_img);
        }
    }

    printf("\n");

    return 0;
}
