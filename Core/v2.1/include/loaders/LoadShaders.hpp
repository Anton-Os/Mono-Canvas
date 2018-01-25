#ifndef LOADERS_H
    #include "Loaders.h"
#endif

#ifndef FILE_IO_H
    #include "loaders/FileIO.hpp"
#endif

#ifndef LOAD_SHADERS_H
    GLuint compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
#define LOAD_SHADERS_H
#endif