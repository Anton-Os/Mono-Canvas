#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Loaders.h"

void printImgData(unsigned char* dataPtr, unsigned dimensions){
    for(unsigned dataOffset = 0; dataOffset < dimensions; dataOffset++)
        std::cout << *(dataPtr + dataOffset) << std::endl;
}

int main(int argc, char** argv) {
    int imgX; int imgY; int imgZ;
    std::string parentDir = getParentDirectory(argv[0]);
    std::string imgFilepath = parentDir + "//res//Smiley.png";
    unsigned char *data = stbi_load(imgFilepath.c_str(), &imgX, &imgY, &imgZ, 4);
    // printImgData(data, imgX * imgY * imgZ);
    stbi_image_free(data);

    return 0;
}
