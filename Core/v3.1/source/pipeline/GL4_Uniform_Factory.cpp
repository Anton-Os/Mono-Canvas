#include "GL4/factory/GL4_Uniform_Factory.hpp"

void GL4_Uniform_Factory::create(){
    mUniforms_b.resize(SHADER_UNIFORM_BASIC_COUNT);
    GL4_Uniform_Basic renderMode(_GL4_Shader_Format::ui, "renderMode");
    mUniforms_b[0] = renderMode;
    mUniform_b_bits.set();
    mUniforms_m.resize(SHADER_UNIFORM_MATRIX_COUNT);
    GL4_Uniform_Matrix mvpMatrix(_GL4_Shader_Format::mat4, "mvpMatrix");
    mUniforms_m[0] = mvpMatrix;
    mUniform_m_bits.set();
}