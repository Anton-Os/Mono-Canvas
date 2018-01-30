#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_UNIFORM_H
    class GL4_Uniform {
    public:
        GL4_Uniform(){}
        GL4_Uniform(const GLuint* progID_arg){
            progID = progID_arg;
        }
        GL4_Uniform(const std::string& name_arg){
            name = name_arg;
        }
        GL4_Uniform(const GLuint* progID_arg, const std::string& name_arg){
            progID = progID_arg;
            name = name_arg;
            location = get_loc(name);
        }
        std::string name;
        const GLuint* progID = nullptr;
        GLint get_loc(const std::string& name_arg){
            char error_progID[] = "progID cannot be a null pointer";
            if(progID == nullptr) logError(__FILE__, __LINE__, error_progID);
            char error_name[] = "name cannot be an empty string";
            if(name.empty()) logError(__FILE__, __LINE__, error_name);

            return glGetUniformLocation(*progID, name.c_str());
        }
    private:
        GLint location;
    };

    struct GL4_Uniform_Basic : public GL4_Uniform {
        GL4_Uniform_Basic(){}
        GL4_Uniform_Basic(const std::string& name_arg) : GL4_Uniform(name_arg){}
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
	    GL4_Uniform_Matrix(){}
        GL4_Uniform_Matrix(const std::string& name_arg) : GL4_Uniform(name_arg){}
        union Type {
            glm::mat2 m2;
            glm::mat3 m3;
            glm::mat4 m4;
        };
    };
#define GL4_UNIFORM_H
#endif