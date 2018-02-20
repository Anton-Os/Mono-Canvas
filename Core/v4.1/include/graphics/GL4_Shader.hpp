#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_LOAD_SHADERS_H
    #include "graphics/GL4_LoadShaders.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "graphics/GL4_Vertex.hpp"
#endif

#ifndef GL4_SHADER_H
    struct GL4_Shader {
        GL4_Shader(const std::string& path_arg, _GL4_Shader_Stage::Pick stage_arg){
            stage = stage_arg;
            filePath = path_arg;
            shaderID = compileShader(filePath);
        }
        GLuint shaderID;
        std::string filePath;
        _GL4_Shader_Stage::Pick stage;
        std::vector<GL4_Shader_Vertex_Format> inputs;
        std::vector<GL4_Shader_Vertex_Format> outputs;
    };
#define GL4_SHADER_H
#endif