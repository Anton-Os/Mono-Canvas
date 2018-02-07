#include "graphics/factory/GL4_Uniform_Factory.hpp"

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
    GL4_Uniform_Basic_Format basic("renderMode", _GL4_Uniform_Basic_Format::f1, _GL4_Uniform_Basic_ID::renderMode);
    return basic;
}

static GL4_Uniform_Matrix_Format gen_uniform_m_mvpMatrix(){
    GL4_Uniform_Matrix_Format matrix("mvpMatrix", _GL4_Uniform_Matrix_Format::m4, _GL4_Uniform_Matrix_ID::mvpMatrix);
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