#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef LOAD_SHADERS_H
    #include "loaders/LoadShaders.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "geometry/GL4_Vertex.hpp"
#endif

#ifndef GL4_SHADER_H
    struct GL4_Shader {
        GL4_Shader(const std::string& path_arg){
            filePath = path_arg;
            shaderID = compileShader(filePath);
        }
        GLuint shaderID;
        std::string filePath;
        _GL4_Shader_Stage::Pick stage;
        std::vector<const GL4_Vertex_Format*> inputs;
        std::vector<const GL4_Vertex_Format*> outputs;
    };
#define GL4_SHADER_H
#endif