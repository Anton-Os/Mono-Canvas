#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef GL4_VERTEX_H
    namespace _vaoPtrModes {
        enum Modes {
            Default,
            Integral,
            Double
        };
    }

    namespace _GL4_Shader_Format {
        enum Type {
            f,
            i,
            ui,
            vec2,
            vec3,
            vec4,
            dvec2,
            dvec3,
            dvec4,
            // Matrix
            mat2,
            mat3,
            mat4
        };
    }

    struct GL4_Vertex_Format {
        GL4_Vertex_Format(){}
        GL4_Vertex_Format(GLuint f, GLint c, GLenum trg, GLenum typ, GLenum u, GLboolean n, GLint v, _GL4_Shader_Format::Type st){ 
            mFeedID = f;
            mCount = c;
            mTarget = trg;
            mType = typ;
            mUsage = u;
            mNormalized = n;
            mVaoPtrMode = v;
            mShader_type = st;
        }
        GLint mFeedID;
        GLint mCount;
        GLenum mTarget;
        GLenum mType;
        GLenum mUsage;
        GLboolean mNormalized;
        GLint mVaoPtrMode;
        _GL4_Shader_Format::Type mShader_type;
    };

    struct GL4_Vertex {
        ~GL4_Vertex(){ glDeleteBuffers(1, &buffer); }
        GLuint buffer = 0;
        const GL4_Vertex_Format* format;
    };

    class GL4_Shader_Vertex_Format {
    public:
        GL4_Shader_Vertex_Format(const _GL4_Shader_Format::Type* shader_type_arg){
            type = shader_type_arg;
        }
        GL4_Shader_Vertex_Format(const _GL4_Shader_Format::Type* shader_type_arg, GLint feedID_arg){
            feedID = feedID_arg;
            overwrite = true;
            type = shader_type_arg;
        }
        bool overwrite = false;
    private:
        GLint feedID;
        const _GL4_Shader_Format::Type* type;
    };
#define GL4_VERTEX_H
#endif