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
    struct GL4_Uniform {
        GL4_Uniform(const GLuint* progID_arg){
            progID = progID_arg;
        }
        GL4_Uniform(const GLuint* progID_arg, const std::string& name_arg){
            progID = progID_arg;
            location = get_loc(name_arg);
        }
        GLint location;
        const GLuint* progID = nullptr;
        std::string name;
        GLint get_loc(const std::string& name_arg){
            return glGetUniformLocation(*progID, name.c_str());
        }
    };

    struct GL4_Uniform_Basic : public GL4_Uniform {
        union Type {
            GLfloat f1;
            GLfloat f2[2];
            GLfloat f3[3];
            GLfloat f4[4];
            GLfloat* fv;
            GLint i1;
            GLint i2[2];
            GLint i3[3];
            GLint i4[4];
            GLint* iv;
            GLuint ui1;
            GLuint ui2[2];
            GLuint ui3[3];
            GLuint ui4[4];
            GLuint* uiv;
        };
    };

    struct GL4_Uniform_Matrix : public GL4_Uniform {
        union Type {
            glm::mat2 m2;
            glm::mat3 m3;
            glm::mat4 m4;
        };
    };

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
        //std::vector<GL4_Uniform_Basic> uniforms_b;
        //std::vector<GL4_Uniform_Matrix> uniforms_m;
    };
#define GL4_SHADER_H
#endif