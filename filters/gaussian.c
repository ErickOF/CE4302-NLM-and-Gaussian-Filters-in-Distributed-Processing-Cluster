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
            *(window) = (uint8_t) *(img + (i * height + m) + j + n);
            window++;
        }
    }
}

void get_gaussian_kernel(float* kernel, int size, double stdev)
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
    }
}

void gaussian_filter(uint8_t* img, uint8_t* filtered, int width, int height, int window_size, double stdev)
{
    int mid_window = (int) (window_size - 1)/2;

    uint8_t* window = calloc(window_size * window_size, sizeof(float));
    float* gaussian_kernel = calloc(window_size * window_size, sizeof(float));

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
                    sum += gaussian_kernel[u*window_size + v] * window[u*window_size + v];
                }
            }

            *(filtered + i*height + j) = (uint8_t) ((int) sum);
        }
    }

    // Free memory
    free(window);
    free(gaussian_kernel);
}


int main(int argc, char* argv[])
{
    printf("\n");

    if (argc == 1)
    {
        printf("Images were not provided.\n");
    }
    else
    {
        for (int i = 1; i < argc; i++)
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

            uint8_t* gray_img = malloc(gray_img_size);

            if (gray_img == NULL)
            {
                printf("Unable to allocate memory for the gray image.\n");
                exit(1);
            }

            rgb2gray(rgb_img, gray_img, img_size);

            // Allocate memory for the filtered image
            uint8_t* filtered_img = malloc(gray_img_size);

            if (filtered_img == NULL)
            {
                printf("Unable to allocate memory for the filtered image.\n");
                exit(1);
            }

            // Gaussian filter
            gaussian_filter(gray_img, filtered_img, width, height, 7, 10);

            char output[36];
            sprintf(output, "%s%d%s", "outputs/gaussian", i, ".jpg");

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
