#include "GL4/factory/GL4_Vertex_Factory.hpp"

static GLint match_vAttrib(_GL4_Vertex_Feed::Pick pick_arg, std::vector<GL4_Vertex_Format>* mFormats){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < mFormats->size(); v++){
        if(pick_arg == mFormats->at(v).mFeedID){
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
    mFormats.resize(VERTEX_FACTORY_ATTRIB_COUNT);
    mFormats[_GL4_Vertex_Feed::pos_3f] = gen_pos_3f_format();
    mFormats[_GL4_Vertex_Feed::color_4f] = gen_color_4f_format();
    mFormats[_GL4_Vertex_Feed::normal_3f] = gen_normal_3f_format();
    mFormats[_GL4_Vertex_Feed::texCoord_2f] = gen_texCoord_2f_format();
    mFormat_bits.set();
}

void GL4_Vertex_Factory::append_format(_GL4_Vertex_Feed::Pick pick_arg){
    GL4_Vertex_Format vertex;
    switch(pick_arg){
        case _GL4_Vertex_Feed::pos_3f :
            mFormats.push_back(gen_pos_3f_format());
            mFormat_bits.set(_GL4_Vertex_Feed::pos_3f);
            break;
        case _GL4_Vertex_Feed::color_4f :
            mFormats.push_back(gen_color_4f_format());
            mFormat_bits.set(_GL4_Vertex_Feed::color_4f);
            break;
        case _GL4_Vertex_Feed::normal_3f :
            mFormats.push_back(gen_normal_3f_format());
            mFormat_bits.set(_GL4_Vertex_Feed::normal_3f);
            break;
        case _GL4_Vertex_Feed::texCoord_2f :
            mFormats.push_back(gen_texCoord_2f_format());
            mFormat_bits.set(_GL4_Vertex_Feed::texCoord_2f);
            break;
    }
}

GL4_Vertex_Format* GL4_Vertex_Factory::get_format(_GL4_Vertex_Feed::Pick pick_arg){
    if(!mFormat_bits.test(pick_arg))
        append_format(pick_arg);

    GLint savedAttrib = match_vAttrib(pick_arg, &mFormats);

    if(savedAttrib < 0) return nullptr;
    else return &mFormats[savedAttrib];
}

_GL4_Shader_Format::Type* GL4_Vertex_Factory::get_shader_format(_GL4_Vertex_Feed::Pick pick_arg){
    if(!mFormat_bits.test(pick_arg))
        append_format(pick_arg);

    GLint savedAttrib = match_vAttrib(pick_arg, &mFormats);

    if(savedAttrib < 0) return nullptr;
    else return &mFormats[savedAttrib].mShader_type;
}