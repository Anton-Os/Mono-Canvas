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

    struct GL4_Vertex {
        GLboolean isFed = false;
        GLuint buffer;
        GLint count = 3;
        GLint feedID = 0;
        GLenum target = GL_ARRAY_BUFFER;
        GLenum type = GL_FLOAT;
        GLenum usage = GL_STATIC_DRAW;
        GLboolean normalized = GL_FALSE;
        GLint vaoPtrMode = vaoPtrModes::Default;
    };

#define GL4_VERTEX_H
#endif