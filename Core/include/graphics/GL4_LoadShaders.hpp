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
    GLuint compileShader(const std::string& filePath_arg, _GL4_Shader_Stage::Pick* stage_arg);
#define GL4_LOAD_SHADERS_H
#endif