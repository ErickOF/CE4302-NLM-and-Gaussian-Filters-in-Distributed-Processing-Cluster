#include <stdint.h>
#include <stdio.h>
#include <sys/param.h>

#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libs/stb/stb_image_write.h"


/**
 * This function converts a RGB image to a gray image.
 *
 * Params:
 *      uint8_t* img - image to convert.
 *      uint8_t* gray_prt - pointer to store the image.
 *      int img_sime - size of the image.
 */
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

/**
 * This function extracts a window of size x size from an image.
 *
 * Params:
 *      uint8_t* img - image.
 *      uint8_t* window - pointer to store the windows.
 *      int i - row in the image to extract the window (center of the
 *              window).
 *      int j - column in the image to extract the window (center of
 *              the window).
 *      int height - number of rows in the image.
 *      int size - size of the window.
 */
void get_window(uint8_t* img, uint8_t* window, int i, int j, int height,
                int size)
{
    // Get the middle of the window
    int mid = (int) (size - 1)/2;

    for (int m = -mid; m < mid + 1; m++)
    {
        for (int n = -mid; n < mid + 1; n++)
        {
            // Store the image pixel in the window
            *window = *(img + i*height + m + j + n);
            window++;
        }
    }
}

/**
 * This function returns a gaussian kernel of size x size and a
 * standard deviation of stddev.
 *
 * Params:
 *      double* kernel - pointer to store the kernel.
 *      int size - size of the kernel.
 *      double stddev - standard deviation of the gaussian
 *                      distribution.
 */
void get_gaussian_kernel(double* kernel, int size, double stdev)
{
    // Get the middle of the window
    double mid = (size - 1)/2.0;
    double sum = 0;
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            // Get x and y values
            double x = i - mid;
            double y = j - mid;

            // Evaluate in the gaussian distribution
            kernel[i*size + j] = exp(-(x*x + y*y)/(2*stdev*stdev));
            sum += kernel[i*size + j];
        }
    }

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            // Normalize
            kernel[i*size + j] /= sum;
        }
    }
}

/**
 * This function performs a gaussian filtering on an image.
 *
 * Params:
 *      uint8_t* img - image to filter.
 *      uint8_t* filtered - pointer to the filtered image.
 *      int width - number of rows.
 *      int height - number of cols.
 *      int window_size - size of the window.
 *      double stdev - standard deviation of the gaussian
 *                     distribution.
 */
void gaussian_filter(uint8_t* img, uint8_t* filtered, int width, int height,
                     int window_size, double stdev)
{
    // Get the middle of the window
    int mid_window = (int) (window_size - 1)/2;

    // Get memory for the windows
    uint8_t* window = (uint8_t*) calloc(window_size * window_size, sizeof(uint8_t));
    double* gaussian_kernel = (double*) calloc(window_size * window_size, sizeof(double));

    // Get the gaussian kernel
    get_gaussian_kernel(gaussian_kernel, window_size, stdev);

    for (int i = window_size; i < width - window_size; i++)
    {
        for (int j = window_size; j < height - window_size; j++)
        {
            double sum = 0.0;

            // Get the window from the image
            get_window(img, window, i, j, height, window_size);

            // Compute the new value for the center pixel
            for (int u = 0; u < window_size; u++)
            {
                for (int v = 0; v < window_size; v++)
                {
                    sum += gaussian_kernel[u*window_size + v]*((double) window[u*window_size + v]);
                }
            }

            uint8_t value = 0;

            // Keep the pixel value between 0 and 255, avoiding
            // unexpected values
            if (sum > 255)
            {
                value = 255;
            } else if (sum > 0)
            {
                value = (uint8_t) sum;
            }

            // Set the pixel
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
        printf("Args were not provided. `make nlm w=3 sigma=2 imgs=\"img1 img2 img3 etc\"`.\n");
    }
    else
    {
        // Convert to numbers
        int win_size = atoi(argv[1]);
        float sigma = atof(argv[2]);

        // Apply the filter to all images
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

            // Gaussian filtering
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
