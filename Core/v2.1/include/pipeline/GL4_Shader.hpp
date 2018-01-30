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
    /* union GL4_Uniform_Basic_t {
        GLfloat f1;
        GLfloat f2[2];
        GLfloat f3[3];
        GLfloat f4[4];
        GLint i1;
        GLint i2[2];
        GLint i3[3];
        GLint i4[4];
        GLuint ui1;
        GLuint ui2[2];
        GLuint ui3[3];
        GLuint ui4[4];
    };

    struct GL4_Uniform_Basic {
        GLint location;
        GL4_Uniform_Basic_t data;
    }; */

    /* union GL4_Uniform_Matrix_t {
        glm::mat2 mat2,
        glm::mat3 mat3,
        glm::mat4 mat4; 
    };

    struct GL4_Uniform_Matrix {
        GLint location;
        GL4_Uniform_Matrix_t data;
    }; */

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
        // std::vector<const GL4_Uniform_Basic> uniforms_b;
        // std::vector<const GL4_Uniform_Matrix> uniforms_m;  
    };
#define GL4_SHADER_H
#endif