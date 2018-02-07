#include "graphics/factory/GL4_Uniform_Factory.hpp"

void GL4_Uniform_Factory::create(){
    mUniforms_b.resize(SHADER_UNIFORM_BASIC_COUNT);
    GL4_Uniform_Basic_Format renderMode("renderMode", _GL4_Uniform_Basic_Format::f1);
    mUniforms_b[0] = renderMode;
    mUniform_b_bits.set();
    mUniforms_m.resize(SHADER_UNIFORM_MATRIX_COUNT);
    GL4_Uniform_Matrix_Format mvpMatrix("mvpMatrix", _GL4_Uniform_Matrix_Format::m4);
    mUniforms_m[0] = mvpMatrix;
    mUniform_m_bits.set();
}