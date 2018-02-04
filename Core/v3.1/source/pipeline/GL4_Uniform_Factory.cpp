#include "GL4/GL4_Uniform_Factory.hpp"

void GL4_Uniform_Factory::create(){
    uniforms_b.resize(SHADER_UNIFORM_BASIC_COUNT);
    GL4_Uniform_Basic renderMode(_GL4_Shader_Format::ui, "renderMode");
    uniforms_b[0] = renderMode;
    uniforms_b.resize(SHADER_UNIFORM_MATRIX_COUNT);
    GL4_Uniform_Matrix mvpMatrix(_GL4_Shader_Format::mat4, "mvpMatrix");
    uniforms_m[0] = mvpMatrix;
    return;
}