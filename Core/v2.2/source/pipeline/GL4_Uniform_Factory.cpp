#include "pipeline/GL4_Uniform_Factory.hpp"

void GL4_Uniform_Factory::create(){
    GL4_Uniform_Basic renderMode("renderMode");
    uniforms_b[0] = renderMode;
    GL4_Uniform_Matrix mvpMatrix("mvpMatrix");
    uniforms_m[0] = mvpMatrix;
    return;
}