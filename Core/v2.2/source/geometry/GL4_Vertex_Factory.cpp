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
    const GL4_Vertex_Format vertex_pos(0, 3, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format::vec3);
    formats[_GL4_Vertex_Feed::pos_3f] = vertex_pos;
    const GL4_Vertex_Format vertex_color(1, 4, GL_ARRAY_BUFFER, GL_UNSIGNED_BYTE, GL_STATIC_DRAW, GL_TRUE, _vaoPtrModes::Default, _GL4_Shader_Format::vec4);
    formats[_GL4_Vertex_Feed::color_4f] = vertex_color;
    const GL4_Vertex_Format vertex_normal(2, 3, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format::vec3);
    formats[_GL4_Vertex_Feed::normal_3f] = vertex_normal;
    const GL4_Vertex_Format vertex_texCoord(3, 2, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format::vec2);
    formats[_GL4_Vertex_Feed::texCoord_2f] = vertex_texCoord;
}

GL4_Vertex_Format* GL4_Vertex_Factory::get_format(GLuint vAttrib_arg){
    GLint savedAttrib = match_vAttrib(vAttrib_arg, formats);

    if(savedAttrib < 0) return nullptr;
    else return &formats[savedAttrib];
}

_GL4_Shader_Format::Type* GL4_Vertex_Factory::get_shader_format(GLuint vAttrib_arg){
    GLint savedAttrib = match_vAttrib(vAttrib_arg, formats);

    if(savedAttrib < 0) return nullptr;
    else return &formats[savedAttrib].shader_type;
}
    