#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "graphics/GL4_Vertex.hpp"
#endif

#define VERTEX_FACTORY_ATTRIB_COUNT 4

#ifndef GL4_VERTEX_FACTORY_H
    class GL4_Vertex_Factory {
    public:
        GL4_Vertex_Format* get_format(_GL4_Vertex_Feed::Pick pick_arg) ;
        _GL4_Shader_Format::Type* get_shader_format(_GL4_Vertex_Feed::Pick pick_arg);
    private:
        std::bitset<VERTEX_FACTORY_ATTRIB_COUNT> mFormat_bits;
        std::vector<GL4_Vertex_Format> mFormats;
        void append_format(_GL4_Vertex_Feed::Pick pick_arg);
        void create();
    };
#define GL4_VERTEX_FACTORY_H
#endif