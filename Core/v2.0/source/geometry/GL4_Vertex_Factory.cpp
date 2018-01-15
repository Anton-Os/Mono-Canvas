#include "geometry/GL4_Vertex_Factory.hpp"

void GL4_Vertex_Factory::create(){
    GL4_Vertex_Format vertex_pos(0, 3, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, vaoPtrModes::Default);
    formats[0] = vertex_pos;
    GL4_Vertex_Format vertex_color(1, 4, GL_ARRAY_BUFFER, GL_UNSIGNED_BYTE, GL_STATIC_DRAW, GL_TRUE, vaoPtrModes::Default);
    formats[1] = vertex_pos;
    GL4_Vertex_Format vertex_normal(2, 3, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, vaoPtrModes::Default);
    formats[2] = vertex_pos;
    GL4_Vertex_Format vertex_texCoord(3, 2, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, vaoPtrModes::Default);
    formats[3] = vertex_pos;
}