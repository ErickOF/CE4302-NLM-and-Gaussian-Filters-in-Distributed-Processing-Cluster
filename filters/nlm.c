#include <stdint.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libs/stb/stb_image_write.h"


int main(int argc, char* argv[])
{
    int width, height, bpp;

    uint8_t* rgb_image = stbi_load("src/input/lena.png", &width, &height, &bpp, 3);

    stbi_write_png("src/output/image.png", width, height, bpp, rgb_image, bpp*width);

    stbi_image_free(rgb_image);

    return 0;
}
