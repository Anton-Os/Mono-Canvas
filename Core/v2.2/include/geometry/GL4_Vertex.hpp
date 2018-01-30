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

    struct GL4_Vertex_Format {
        GL4_Vertex_Format(){}
        GL4_Vertex_Format(GLuint f, GLint c, GLenum trg, GLenum typ, GLenum u, GLboolean n, GLint v){ 
            feedID = f;
            count = c;
            target = trg;
            type = typ;
            usage = u;
            normalized = n;
            vaoPtrMode = v;
        }
        GLint feedID;
        GLint count;
        GLenum target;
        GLenum type;
        GLenum usage;
        GLboolean normalized;
        GLint vaoPtrMode;
    };

    struct GL4_Vertex {
        ~GL4_Vertex(){ glDeleteBuffers(1, &buffer); }
        GLuint buffer = 0;
        const GL4_Vertex_Format* format;
    };

    // Alternative vertex format capable of overriding shader input and output locations
    /* class GL4_Vertex_Format_Alt {
    public:
	void set_override(bool override_arg){ override = override_arg; }
	bool get_override(){ return override }
	void set_feedID(GLint feedID_arg){ feedID = feedID_arg; }
	GLint get_feedID(){ return feedID; }
    private:
	GLint feedID = 0;
	const GL4_Vertex_Format* format;
    }; */
#define GL4_VERTEX_H
#endif