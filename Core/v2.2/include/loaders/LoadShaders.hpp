#ifndef LOADERS_H
    #include "Loaders.h"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef FILE_IO_H
    #include "loaders/FileIO.hpp"
#endif

#ifndef LOAD_SHADERS_H
    GLuint compileShader(const std::string& filePath_arg);
    GLuint compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
#define LOAD_SHADERS_H
#endif