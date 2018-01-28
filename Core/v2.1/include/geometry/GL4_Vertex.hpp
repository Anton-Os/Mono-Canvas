#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef GL4_SHADER_TYPES_H
    #include "pipeline/GL4_Shader_Types.hpp"
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
        GL4_Vertex_Format(){}
        GL4_Vertex_Format(GLuint f, GLint c, GLenum trg, GLenum typ, GLenum u, GLboolean n, GLint v, 
                          const std::string& nm, const std::string& g){
            feedID = f;
            count = c;
            target = trg;
            type = typ;
            usage = u;
            normalized = n;
            vaoPtrMode = v;
            glsl_type.create(nm, g);
        }
        GLint feedID;
        GLint count;
        GLenum target;
        GLenum type;
        GLenum usage;
        GLboolean normalized;
        GLint vaoPtrMode;
        GL4_Shader_Type glsl_type;

    };

    struct GL4_Vertex {
        ~GL4_Vertex(){ glDeleteBuffers(1, &buffer); }
        GLuint buffer = 0;
        const GL4_Vertex_Format* format;
    };
#define GL4_VERTEX_H
#endif