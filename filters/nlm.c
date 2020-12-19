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
 * This function substracts two kernels.
 *
 * Params:
 *      uint8_t* v - first kernel.
 *      uint8_t* u - second kernel.
 *      double* result_window - result of the operation.
 *      int size - size of the window
 */
void substract(uint8_t* v, uint8_t* u, double* result_window, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // Substract and store the result
            result_window[i*size + j] = ((double) v[i*size + j]) - ((double) u[i*size + j]);
        }
    }
}

/**
 * This function computes the norm of a kernel as a flatten vector.
 *
 * Params:
 *      double* v - kernel to use.
 *      int size - size of the kernel.
 */
double norm(double* v, int size)
{
    double sum = 0.0;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // Sum of squares
            sum += pow(v[i*size + j], 2.0);
        }
    }

    // Compute the square root to get the result
    return sqrt(sum);
}

/**
 * This function performs a non-local means filtering on an image.
 *
 * Params:
 *      uint8_t* img - image to filter.
 *      uint8_t* filtered - pointer to the filtered image.
 *      int width - number of cols.
 *      int height - number of rows.
 *      int window_size - size of the window.
 *      int sim_window_size - size of the similarity window.
 *      double stdev - standard deviation of the gaussian
 *                     distribution.
 */
void nlm_filter(uint8_t* img, uint8_t* filtered, int width, int height,
                int window_size, int sim_window_size, double stdev)
{
    // Get the middle of the windows
    int mid_window = (int) (window_size - 1)/2;
    int mid_sim_window = (int) (sim_window_size - 1)/2;

    // Get memory for the windows
    uint8_t* window = (uint8_t*) calloc(window_size*window_size, sizeof(uint8_t));
    uint8_t* sim_window = (uint8_t*) calloc(window_size*window_size, sizeof(uint8_t));
    double* result_window = (double*) calloc(window_size*window_size, sizeof(double));

    for (int i = window_size; i < height - window_size; i++)
    {
        for (int j = window_size; j < width - window_size; j++)
        {
            double sum = 0.0;

            // Get the window from the image
            get_window(img, window, i, j, height, window_size);

            // Values for the similarity window
            int umin = MAX(i - mid_sim_window, mid_window);
            int umax = MIN(i + mid_sim_window, height - mid_window);
            int vmin = MAX(j - mid_sim_window, mid_window);
            int vmax = MIN(j + mid_sim_window, width - mid_window);

            double normalization_factor = 0.0;

            // Compare window against the similarity window
            for (int u = umin; u < umax + 1; u++)
            {
                for (int v = vmin; v < vmax + 1; v++)
                {
                    // Get the similarity window from the image
                    get_window(img, sim_window, u, v, height, window_size);

                    // Similarity between pixels
                    substract(window, sim_window, result_window, window_size);
                    double norm_value = norm(result_window, window_size);
                    double similarity = exp(-norm_value/pow(stdev, 2.0));

                    normalization_factor += similarity;
                    sum += similarity*img[u*width + v];
                }
            }

            // Normalize the resulting pixel
            double result = sum/normalization_factor;
            uint8_t value = 0;

            // Keep the pixel value between 0 and 255, avoiding
            // unexpected values
            if (result > 255)
            {
                value = 255;
            } else if (result > 0)
            {
                value = (uint8_t) round(result);
            }

            filtered[i*width + j] = value;
        }
    }

    // Free memory
    free(window);
    free(sim_window);
    free(result_window);
}


int main(int argc, char* argv[])
{
    if (argc < 5)
    {
        printf("Args were not provided. `make nlm w=3 sw=7 sigma=2.0 imgs=\"img1 img2 img3 etc\"`.\n");
    }
    else
    {
        // Convert to numbers
        int win_size = atoi(argv[1]);
        int sim_win_size = atoi(argv[2]);
        float sigma = atof(argv[3]);

        for (int i = 4; i < argc; i++)
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
            size_t img_size = width*height*channels;
            size_t gray_img_size = width*height;

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

            // Non-Local Means filtering
            nlm_filter(gray_img, filtered_img, width, height, win_size, sim_win_size, sigma);

            char output[21];
            sprintf(output, "%s%d%s", "outputs/nlm", i - 4, ".png");

            // Save image
            stbi_write_jpg(output, width, height, 1, filtered_img, width);

            // Free memory
            stbi_image_free(rgb_img);
            stbi_image_free(gray_img);
            stbi_image_free(filtered_img);
        }
    }

    return 0;
}
