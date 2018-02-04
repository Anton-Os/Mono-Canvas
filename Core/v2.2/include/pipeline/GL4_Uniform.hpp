#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "geometry/GL4_Vertex.hpp"
#endif

#ifndef GL4_UNIFORM_H
    class GL4_Uniform {
    public:
        GL4_Uniform(){}
        //GL4_Uniform(const std::string& name_arg){}
        GL4_Uniform(_GL4_Shader_Format::Type shader_type_arg, const std::string& name_arg){
            shader_type = shader_type_arg;
            name = name_arg;
        }
        GL4_Uniform(_GL4_Shader_Format::Type shader_type_arg, const std::string& name_arg, const GLuint* progID_arg){
            init(shader_type_arg, progID_arg, name_arg);
            get_loc();
        }
        // void init(const GLuint* progID_arg);
        // void init(const std::string& name_arg);
        void init(const GLuint* progID_arg);
        void get_loc();
    protected:
        void init(_GL4_Shader_Format::Type shader_type_arg, const GLuint* progID_arg, const std::string& name_arg);
        _GL4_Shader_Format::Type shader_type;
        bool initPhase = false;
        std::string name;
        const GLuint* progID = nullptr;
        GLint location;
    };

    struct GL4_Uniform_Basic : public GL4_Uniform {
        GL4_Uniform_Basic(){}
        GL4_Uniform_Basic(_GL4_Shader_Format::Type shader_type_arg, const std::string& name_arg) : GL4_Uniform(shader_type_arg, name_arg){}
        void set(void* data);
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
        } type;
    };

    struct GL4_Uniform_Matrix : public GL4_Uniform {
	    GL4_Uniform_Matrix(){}
        GL4_Uniform_Matrix(_GL4_Shader_Format::Type shader_type_arg, const std::string& name_arg) : GL4_Uniform(shader_type_arg, name_arg){}
        void set(void* data);
        union Type {
            glm::mat2 m2;
            glm::mat3 m3;
            glm::mat4 m4;
        };
    };
#define GL4_UNIFORM_H
#endif