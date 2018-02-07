#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_UNIFORM_H
    struct GL4_Uniform_Format {
        std::string mName;
        bool mReady = false;
    };

    namespace _GL4_Uniform_Basic_Format {
        enum Pick {
            f1,
            i1,
            ui1
        };
    }

    struct GL4_Uniform_Basic_Format : public GL4_Uniform_Format {
        GL4_Uniform_Basic_Format(){}
        GL4_Uniform_Basic_Format(const std::string& name_arg, _GL4_Uniform_Basic_Format::Pick pick_arg, _GL4_Uniform_Basic_ID::Pick id_arg){
            mName = name_arg;
            mPick = pick_arg;
            mID = id_arg;
            mReady = true;
        }
        _GL4_Uniform_Basic_Format::Pick mPick;
        _GL4_Uniform_Basic_ID::Pick mID;
    };
    
    namespace _GL4_Uniform_Matrix_Format {
        enum Pick {
            m2,
            m3,
            m4
        };
    }

    struct GL4_Uniform_Matrix_Format : public GL4_Uniform_Format {
        GL4_Uniform_Matrix_Format(){}
        GL4_Uniform_Matrix_Format(const std::string& name_arg, _GL4_Uniform_Matrix_Format::Pick pick_arg, _GL4_Uniform_Matrix_ID::Pick id_arg){
            mName = name_arg;
            mPick = pick_arg;
            mID = id_arg;
        }
        _GL4_Uniform_Matrix_Format::Pick mPick;
        _GL4_Uniform_Matrix_ID::Pick mID;
    };

    class GL4_Uniform {
    public:
        GL4_Uniform(){}
        GL4_Uniform(const GLuint* progID_arg){
            mProgID = progID_arg;
        }
        GLint get_loc(const std::string& name_arg);
    protected:
        bool mReady;
        const GLuint* mProgID;
        GLint mLocation;
    };

    class GL4_Uniform_Basic : public GL4_Uniform {
    public:
        GL4_Uniform_Basic(){}
        GL4_Uniform_Basic(const GLuint* progID_arg, const GL4_Uniform_Basic_Format* format_arg){
            init(progID_arg, format_arg);
        }
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
        } mType;
        void init(const GLuint* progID_arg, const GL4_Uniform_Basic_Format* format_arg);
        void get_loc(){ mLocation = GL4_Uniform::get_loc(mFormat->mName); }
        void set(void* data);
    private:
        const GL4_Uniform_Basic_Format* mFormat;
    };

    class GL4_Uniform_Matrix : public GL4_Uniform {
    public:
        GL4_Uniform_Matrix(){}
        GL4_Uniform_Matrix(const GLuint* progID_arg, const GL4_Uniform_Matrix_Format* format_arg){
            mProgID = progID_arg;
            mFormat = format_arg;
            mReady = true;
        }
        union Type {
            GLfloat mat2[4];
            GLfloat mat3[9];
            GLfloat mat4[16];
        } mType;
        void init(const GLuint* progID_arg, const GL4_Uniform_Matrix_Format* format_arg);
        void get_loc(){ mLocation = GL4_Uniform::get_loc(mFormat->mName); }
        void set(void* data);
    private:
        const GL4_Uniform_Matrix_Format* mFormat;
    };
#define GL4_UNIFORM_H
#endif