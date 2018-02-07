#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "graphics/GL4_Vertex.hpp"
#endif

#ifndef GL4_UNIFORM_H
    class GL4_Uniform {
    public:
        GL4_Uniform(){}
        void init(const GLuint* progID_arg);
        void get_loc();
    protected:
        bool mReady = false;
        std::string mName;
        const GLuint* mProgID = nullptr;
        GLint mLocation;
    };

    namespace _GL4_Uniform_Basic_Format {
        enum Pick {
            f1,
            i1,
            ui1
        };
    }

    struct GL4_Uniform_Basic : public GL4_Uniform {
        GL4_Uniform_Basic(){}
        GL4_Uniform_Basic(_GL4_Uniform_Basic_Format::Pick type_arg, const std::string& name_arg){
            mFormat = type_arg;
            mName = name_arg;
        }
        GL4_Uniform_Basic(_GL4_Uniform_Basic_Format::Pick type_arg, const GLuint* progID_arg, const std::string& name_arg){
            mFormat = type_arg;
            mName = name_arg;
            mProgID = progID_arg;
            mReady = true;
        }
        void set(void* data);
        _GL4_Uniform_Basic_Format::Pick mFormat;
        union Type {
            Type(){ i1 = 0; }
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
        } mType;
    };

    namespace _GL4_Uniform_Matrix_Format {
        enum Pick {
            mat2,
            mat3,
            mat4
        };
    }

    struct GL4_Uniform_Matrix : public GL4_Uniform {
	    GL4_Uniform_Matrix(){}
        GL4_Uniform_Matrix(_GL4_Uniform_Matrix_Format::Pick type_arg, const std::string& name_arg){
            mFormat = type_arg;
            mName = name_arg;
        }
        GL4_Uniform_Matrix(_GL4_Uniform_Matrix_Format::Pick type_arg, const GLuint* progID_arg, const std::string& name_arg){
            mFormat = type_arg;
            mName = name_arg;
            mProgID = progID_arg;
            mReady = true;
        }
        void set(void* data);
        _GL4_Uniform_Matrix_Format::Pick mFormat;
        union Type {
            Type(){ m4 = glm::mat4(1); }
            glm::mat2 m2;
            glm::mat3 m3;
            glm::mat4 m4;
        } mType;
    };
#define GL4_UNIFORM_H
#endif