#include "pipeline/GL4_Uniform_Factory.hpp"

void GL4_Uniform_Factory::create(){
    GL4_Uniform_Basic renderMode(_GL4_Shader_Format::ui, "renderMode");
    uniforms_b[0] = renderMode;
    GL4_Uniform_Matrix mvpMatrix(_GL4_Shader_Format::mat4, "mvpMatrix");
    uniforms_m[0] = mvpMatrix;
    return;
}