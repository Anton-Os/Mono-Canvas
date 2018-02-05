#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "GL4/GL4_Vertex.hpp"
#endif

#define VERTEX_FACTORY_ATTRIB_COUNT 4

#ifndef GL4_VERTEX_FACTORY_H
    // static GLint match_vAttrib(GLuint vAttrib, const GL4_Vertex_Format* formatPtr);
    
    class GL4_Vertex_Factory {
    public:
        GL4_Vertex_Format* get_format(_GL4_Vertex_Feed::Pick pick_arg) ;
        _GL4_Shader_Format::Type* get_shader_format(_GL4_Vertex_Feed::Pick pick_arg);
    private:
        std::bitset<VERTEX_FACTORY_ATTRIB_COUNT> format_bits;
        std::vector<GL4_Vertex_Format> formats;
        void append_format(_GL4_Vertex_Feed::Pick pick_arg);
        void create();
    };
#define GL4_VERTEX_FACTORY_H
#endif