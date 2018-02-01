#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "geometry/GL4_Vertex.hpp"
#endif

#define VERTEX_FACTORY_ATTRIB_COUNT 4

#ifndef GL4_VERTEX_FACTORY_H
    // static GLint match_vAttrib(GLuint vAttrib, const GL4_Vertex_Format* formatPtr);
    
    class GL4_Vertex_Factory {
    public:
        GL4_Vertex_Factory(){ create(); }
        ~GL4_Vertex_Factory(){ delete[] formats; }
        GL4_Vertex_Format* get_format(GLuint vAttrib);
        _GL4_Shader_Format::Type* get_shader_format(GLuint vAttrib_arg);
    private:
        GL4_Vertex_Format* formats = new GL4_Vertex_Format[VERTEX_FACTORY_ATTRIB_COUNT];
        void create();
    };
#define GL4_VERTEX_FACTORY_H
#endif