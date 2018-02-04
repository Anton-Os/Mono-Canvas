#ifndef LOADERS_H
    #include "Loaders.h"
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

GLuint createTexture_stbi(const char* Filename){
    GLint ImgX, ImgY, Channels;

    GLubyte *ImgData = stbi_load(Filename, &ImgX, &ImgY, &Channels, 4);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, ImgX, ImgY);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ImgX, ImgY, GL_RGBA, GL_UNSIGNED_BYTE, ImgData);
    return texture;
}