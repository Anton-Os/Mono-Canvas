#include "graphics/factory/GL4_Vertex_Factory.hpp"

static char error_formatSupport[] = "Format not supported";
static char error_dynamicMode[] = "Cannot invoke create(), vertex factory is dynamic";

static GL4_Vertex_Format gen_pos_3f_format(){
    GL4_Vertex_Format vertex(_GL4_Vertex_Feed_ID::pos_3f, 3, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format_ID::vec3);
    return vertex;
}

static GL4_Vertex_Format gen_pos_2f_format(){
    GL4_Vertex_Format vertex(_GL4_Vertex_Feed_ID::pos_2f, 2, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format_ID::vec3);
    return vertex;
}

static GL4_Vertex_Format gen_color_4f_format(){
    GL4_Vertex_Format vertex(_GL4_Vertex_Feed_ID::color_4f, 4, GL_UNSIGNED_BYTE, GL_STATIC_DRAW, GL_TRUE, _vaoPtrModes::Default, _GL4_Shader_Format_ID::vec4);
    return vertex;
}

static GL4_Vertex_Format gen_normal_3f_format(){
    GL4_Vertex_Format vertex(_GL4_Vertex_Feed_ID::normal_3f, 3, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format_ID::vec3);
    return vertex;
}

static GL4_Vertex_Format gen_texCoord_2f_format(){
    GL4_Vertex_Format vertex(_GL4_Vertex_Feed_ID::texCoord_2f, 2, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format_ID::vec2);
    return vertex;
}

static GL4_Vertex_Format gen_frag_4f_format(){
    GL4_Vertex_Format vertex(_GL4_Vertex_Feed_ID::frag_4f, 4, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, _vaoPtrModes::Default, _GL4_Shader_Format_ID::vec4);
    return vertex;
}

static GLuint appendFormat(_GL4_Vertex_Feed_ID::Pick vertexID_arg, std::vector<GL4_Vertex_Format>* feeds_arg){
    switch(vertexID_arg){
        case _GL4_Vertex_Feed_ID::pos_3f:
            feeds_arg->push_back(gen_pos_3f_format());
            break;
        case _GL4_Vertex_Feed_ID::pos_2f:
            feeds_arg->push_back(gen_pos_2f_format());
            break;
        case _GL4_Vertex_Feed_ID::color_4f:
            feeds_arg->push_back(gen_color_4f_format());
            break;
        case _GL4_Vertex_Feed_ID::normal_3f:
            feeds_arg->push_back(gen_normal_3f_format());
            break;
        case _GL4_Vertex_Feed_ID::texCoord_2f:
            feeds_arg->push_back(gen_texCoord_2f_format());
            break;
        case _GL4_Vertex_Feed_ID::frag_4f:
            feeds_arg->push_back(gen_frag_4f_format());
            break;
        default:
            logError(__FILE__, __LINE__, error_formatSupport);
            break;
    }
    return feeds_arg->size() - 1;
}

GL4_Vertex_Format* GL4_Vertex_Factory::get_format(_GL4_Vertex_Feed_ID::Pick vertexID_arg){
    if(mStaticMode) return &mFormats[vertexID_arg];
    else if(! mFormatBits.test(vertexID_arg)){
        mFormatIndices[vertexID_arg] = appendFormat(vertexID_arg, &mFormats);
        mFormatBits.set(vertexID_arg);
    }
    return &mFormats[mFormatIndices[vertexID_arg]];
}

void GL4_Vertex_Factory::create(){
    if(mFormats.empty()) logError(__FILE__, __LINE__, error_dynamicMode);
    mFormats.resize(VERTEX_FACTORY_ENTRY_COUNT);
    mFormats[_GL4_Vertex_Feed_ID::pos_3f] = gen_pos_3f_format();
    mFormats[_GL4_Vertex_Feed_ID::pos_2f] = gen_pos_2f_format();
    mFormats[_GL4_Vertex_Feed_ID::color_4f] = gen_color_4f_format();
    mFormats[_GL4_Vertex_Feed_ID::normal_3f] = gen_normal_3f_format();
    mFormats[_GL4_Vertex_Feed_ID::texCoord_2f] = gen_texCoord_2f_format();
    mFormats[_GL4_Vertex_Feed_ID::frag_4f] = gen_frag_4f_format();
    mFormatBits.set();
    mStaticMode = true;
}