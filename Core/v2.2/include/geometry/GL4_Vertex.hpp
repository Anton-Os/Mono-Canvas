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
            dvec4
        };
    }

    struct GL4_Vertex_Format {
        GL4_Vertex_Format(){}
        GL4_Vertex_Format(GLuint f, GLint c, GLenum trg, GLenum typ, GLenum u, GLboolean n, GLint v, _GL4_Shader_Format::Type st){ 
            feedID = f;
            count = c;
            target = trg;
            type = typ;
            usage = u;
            normalized = n;
            vaoPtrMode = v;
            shader_type = st;
        }
        GLint feedID;
        GLint count;
        GLenum target;
        GLenum type;
        GLenum usage;
        GLboolean normalized;
        GLint vaoPtrMode;
        _GL4_Shader_Format::Type shader_type;
    };

    struct GL4_Vertex {
        ~GL4_Vertex(){ glDeleteBuffers(1, &buffer); }
        GLuint buffer = 0;
        const GL4_Vertex_Format* format;
    };

    // Alternative vertex format capable of overriding shader input and output locations
    /*class GL4_Vertex_Format_Alt {
    public:
        GL4_Vertex_Format_Alt(){}
        GL4_Vertex_Format_Alt(const GL4_Vertex_Format* format_arg){
            set_format(format_arg);
        }
        GL4_Vertex_Format_Alt(GLuint feedID_arg, const GL4_Vertex_Format* format_arg){
            set_feedID(feedID_arg);
            set_format(format_arg);
        }
        void set_format(const GL4_Vertex_Format* format_arg){
            format = format_arg;
        }
	    void set_feedID(GLint feedID_arg){ 
            overwrite = true;
            feedID = feedID_arg; 
        }
	    GLint get_feedID(){ return feedID; }
        bool overwrite = false;
    private:
	    GLint feedID = 0;
	    const GL4_Vertex_Format* format;
    }; */

    class GL4_Vertex_Format_Alt {
    public:
        GL4_Vertex_Format_Alt(const _GL4_Shader_Format::Type* shader_type_arg){
            type = shader_type_arg;
        }
        GL4_Vertex_Format_Alt(const _GL4_Shader_Format::Type* shader_type_arg, GLint feedID_arg){
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