#include "graphics/factory/GL4_Uniform_Factory.hpp"

static char error_findFormat[] = "Requested format could not be obtained";
static char error_formatNotReady[] = "Uniform format hasnt been properly initialized";

static GLint match_vAttrib(_GL4_Uniform_Basic_ID::Pick pick_arg, std::vector<GL4_Uniform_Basic_Format>* formats_arg){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < formats_arg->size(); v++){
        if(pick_arg == formats_arg->at(v).mID){
            savedAttrib = v;
            break;
        }
    }
    return savedAttrib;
}

static GLint match_vAttrib(_GL4_Uniform_Matrix_ID::Pick pick_arg, std::vector<GL4_Uniform_Matrix_Format>* formats_arg){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < formats_arg->size(); v++){
        if(pick_arg == formats_arg->at(v).mID){
            savedAttrib = v;
            break;
        }
    }
    return savedAttrib;
}

static GL4_Uniform_Basic_Format gen_uniform_b_renderMode(){
    GL4_Uniform_Basic_Format basic(_GL4_Uniform_Basic_ID::renderMode, "renderMode", _GL4_Uniform_Basic_Format::ui1);
    return basic;
}

static GL4_Uniform_Matrix_Format gen_uniform_m_mvpMatrix(){
    GL4_Uniform_Matrix_Format matrix( _GL4_Uniform_Matrix_ID::mvpMatrix, "mvpMatrix", _GL4_Uniform_Matrix_Format::m4);
    return matrix;
}

void GL4_Uniform_Factory::create(){
    mUniforms_b.resize(SHADER_UNIFORM_BASIC_COUNT);
    mUniforms_b[_GL4_Uniform_Basic_ID::renderMode] = gen_uniform_b_renderMode();
    mUniform_b_bits.set();
    mUniforms_m.resize(SHADER_UNIFORM_MATRIX_COUNT);
    mUniforms_m[_GL4_Uniform_Matrix_ID::mvpMatrix] = gen_uniform_m_mvpMatrix();
    mUniform_m_bits.set();
}

void GL4_Uniform_Factory::append_uniform_b(_GL4_Uniform_Basic_ID::Pick uniform_b_arg){
    GL4_Uniform_Basic_Format basic;
    switch(uniform_b_arg){
        case _GL4_Uniform_Basic_ID::renderMode :
            mUniforms_b.push_back(gen_uniform_b_renderMode());
            mUniform_b_bits.set(uniform_b_arg);
            break;
    }
}

GL4_Uniform_Basic_Format* GL4_Uniform_Factory::get_uniform_b(_GL4_Uniform_Basic_ID::Pick uniform_b_arg){
    /* if(mUniform_b_bits.all()){
        if(!mUniforms_b[uniform_b_arg].mReady) logError(__FILE__, __LINE__, error_formatNotReady);
        else return &mUniforms_b[uniform_b_arg];
    } */
    if(!mUniform_b_bits.test(uniform_b_arg))
        append_uniform_b(uniform_b_arg);

    GLint savedAttrib = match_vAttrib(uniform_b_arg, &mUniforms_b);

    if(savedAttrib < 0) logError(__FILE__, __LINE__, error_findFormat);
    else return &mUniforms_b[savedAttrib];
}

void GL4_Uniform_Factory::append_uniform_m(_GL4_Uniform_Matrix_ID::Pick uniform_m_arg){
    switch(uniform_m_arg){
        case _GL4_Uniform_Matrix_ID::mvpMatrix :
            mUniforms_m.push_back(gen_uniform_m_mvpMatrix());
            break;
    }
    mUniform_m_bits.set(uniform_m_arg);
}

GL4_Uniform_Matrix_Format* GL4_Uniform_Factory::get_uniform_m(_GL4_Uniform_Matrix_ID::Pick uniform_m_arg){
    /* if(mUniform_m_bits.all()){
        if(!mUniforms_m[uniform_m_arg].mReady) logError(__FILE__, __LINE__, error_formatNotReady);
        else return &mUniforms_m[uniform_m_arg];
    } */
    if(!mUniform_m_bits.test(uniform_m_arg))
        append_uniform_m(uniform_m_arg);

    GLint savedAttrib = match_vAttrib(uniform_m_arg, &mUniforms_m);

    if(savedAttrib < 0) logError(__FILE__, __LINE__, error_findFormat);
    else return &mUniforms_m[savedAttrib];
}