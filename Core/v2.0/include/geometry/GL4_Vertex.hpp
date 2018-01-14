#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef GL4_VERTEX_H
    namespace vaoPtrModes {
        enum Modes {
            Default,
            Integral,
            Double
        };
    }

    struct GL4_Vertex_Format {
        GL4_Vertex_Format(GLuint f, GLint c, GLenum trg, GLenum typ, GLenum u, GLboolean n, GLint v){
            feedID = f;
            count = c;
            target = trg;
            type = typ;
            usage = u;
            normalized = n;
            vaoPtrMode = v;
        }
        GLboolean isFed;
        GLuint buffer;
        GLint feedID;
        GLint count;
        GLenum target;
        GLenum type;
        GLenum usage;
        GLboolean normalized;
        GLint vaoPtrMode;
    };

    // Next commit
    /* struct GL4_Vertex {
        GLuint buffer = 0;
        const GL4_Vertex_Format* format;
    }; */

    struct GL4_Vertex {
        GL4_Vertex(){};
        GL4_Vertex(GLuint f, GLint c, GLenum trg, GLenum typ, GLenum u, GLboolean n, GLint v){
            feedID = f;
            count = c;
            target = trg;
            type = typ;
            usage = u;
            normalized = n;
            vaoPtrMode = v;
        }
        GLboolean isFed = false;
        GLuint buffer;
        GLint feedID = 0;
        GLint count = 3;
        GLenum target = GL_ARRAY_BUFFER;
        GLenum type = GL_FLOAT;
        GLenum usage = GL_STATIC_DRAW;
        GLboolean normalized = GL_FALSE;
        GLint vaoPtrMode = vaoPtrModes::Default;
    };
#define GL4_VERTEX_H
#endif