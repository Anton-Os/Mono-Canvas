#include "geometry/GL4_Vertex_Factory.hpp"

static GLint match_vAttrib(GLuint vAttrib, const GL4_Vertex_Format* formatPtr){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < VERTEX_FACTORY_ATTRIB_COUNT; v++){
        if(vAttrib == (formatPtr + v)->feedID){
            savedAttrib = v;
            break;
        }
    }
    return savedAttrib;
}

void GL4_Vertex_Factory::create(){
    const GL4_Vertex_Format vertex_pos(0, 3, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default);
    formats[_GL4_Vertex_Feed::pos_3f] = vertex_pos;
    const GL4_Vertex_Format vertex_color(1, 4, GL_ARRAY_BUFFER, GL_UNSIGNED_BYTE, GL_STATIC_DRAW, GL_TRUE, _vaoPtrModes::Default);
    formats[_GL4_Vertex_Feed::color_4f] = vertex_color;
    const GL4_Vertex_Format vertex_normal(2, 3, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default);
    formats[_GL4_Vertex_Feed::normal_3f] = vertex_normal;
    const GL4_Vertex_Format vertex_texCoord(3, 2, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default);
    formats[_GL4_Vertex_Feed::texCoord_2f] = vertex_texCoord;
}

GL4_Vertex_Format* GL4_Vertex_Factory::get_format(GLuint vAttrib){
    GLint savedAttrib = match_vAttrib(vAttrib, formats);

    if(savedAttrib < 0) return nullptr;
    else return &formats[savedAttrib];
}