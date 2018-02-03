#include "geometry/GL4_Vertex_Factory.hpp"

static GLint match_vAttrib(_GL4_Vertex_Feed::Pick pick_arg, const GL4_Vertex_Format* formatPtr){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < VERTEX_FACTORY_ATTRIB_COUNT; v++){
        if(pick_arg == (formatPtr + v)->feedID){
            savedAttrib = v;
            break;
        }
    }
    return savedAttrib;
}

static GLint match_vAttrib(_GL4_Vertex_Feed::Pick pick_arg, std::vector<GL4_Vertex_Format>* formats){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < formats->size(); v++){
        if(pick_arg == formats->at(v).feedID){
            savedAttrib = v;
            break;
        }
    }
    return savedAttrib;
}

static GL4_Vertex_Format gen_pos_3f_format(){
    GL4_Vertex_Format vertex(0, 3, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format::vec3);
    return vertex;
}

static GL4_Vertex_Format gen_color_4f_format(){
    GL4_Vertex_Format vertex(1, 4, GL_ARRAY_BUFFER, GL_UNSIGNED_BYTE, GL_STATIC_DRAW, GL_TRUE, _vaoPtrModes::Default, _GL4_Shader_Format::vec4);
    return vertex;
}

static GL4_Vertex_Format gen_normal_3f_format(){
    GL4_Vertex_Format vertex(2, 3, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format::vec3);
    return vertex;
}

static GL4_Vertex_Format gen_texCoord_2f_format(){
    GL4_Vertex_Format vertex(3, 2, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format::vec2);
    return vertex;
}

void GL4_Vertex_Factory::create(){
    formats.resize(VERTEX_FACTORY_ATTRIB_COUNT);
    const GL4_Vertex_Format vertex_pos(0, 3, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format::vec3);
    formats[_GL4_Vertex_Feed::pos_3f] = vertex_pos;
    const GL4_Vertex_Format vertex_color(1, 4, GL_ARRAY_BUFFER, GL_UNSIGNED_BYTE, GL_STATIC_DRAW, GL_TRUE, _vaoPtrModes::Default, _GL4_Shader_Format::vec4);
    formats[_GL4_Vertex_Feed::color_4f] = vertex_color;
    const GL4_Vertex_Format vertex_normal(2, 3, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format::vec3);
    formats[_GL4_Vertex_Feed::normal_3f] = vertex_normal;
    const GL4_Vertex_Format vertex_texCoord(3, 2, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format::vec2);
    formats[_GL4_Vertex_Feed::texCoord_2f] = vertex_texCoord;
    format_bits.set();
}

void GL4_Vertex_Factory::append_format(_GL4_Vertex_Feed::Pick pick_arg){
    GL4_Vertex_Format vertex;
    switch(pick_arg){
        case _GL4_Vertex_Feed::pos_3f :
            formats.push_back(gen_pos_3f_format());
            format_bits.set(_GL4_Vertex_Feed::pos_3f);
            break;
        case _GL4_Vertex_Feed::color_4f :
            formats.push_back(gen_color_4f_format());
            format_bits.set(_GL4_Vertex_Feed::color_4f);
            break;
        case _GL4_Vertex_Feed::normal_3f :
            formats.push_back(gen_normal_3f_format());
            format_bits.set(_GL4_Vertex_Feed::normal_3f);
            break;
        case _GL4_Vertex_Feed::texCoord_2f :
            formats.push_back(gen_texCoord_2f_format());
            format_bits.set(_GL4_Vertex_Feed::texCoord_2f);
            break;
    }
}

GL4_Vertex_Format* GL4_Vertex_Factory::get_format(_GL4_Vertex_Feed::Pick pick_arg){
    if(!format_bits.test(pick_arg))
        append_format(pick_arg);

    GLint savedAttrib = match_vAttrib(pick_arg, &formats);

    if(savedAttrib < 0) return nullptr;
    else return &formats[savedAttrib];
}

_GL4_Shader_Format::Type* GL4_Vertex_Factory::get_shader_format(_GL4_Vertex_Feed::Pick pick_arg){
    GLint savedAttrib = match_vAttrib(pick_arg, formats.data());

    if(savedAttrib < 0) return nullptr;
    else return &formats[savedAttrib].shader_type;
}