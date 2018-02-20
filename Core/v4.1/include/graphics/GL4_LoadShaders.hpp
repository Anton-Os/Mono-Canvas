#define PIPELINE_X
#define GEOMETRY_X
#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef FILE_IO_H
    #include "loaders/FileIO.hpp"
#endif

#ifndef GL4_LOAD_SHADERS_H
    GLuint compileShader(const std::string& filePath_arg);
    GLuint compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
#define GL4_LOAD_SHADERS_H
#endif