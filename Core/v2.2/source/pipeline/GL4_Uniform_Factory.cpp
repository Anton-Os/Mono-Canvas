#include "pipeline/GL4_Uniform_Factory.hpp"

void GL4_Uniform_Factory::create(){
    GL4_Uniform_Basic renderMode("renderMode");
    GL4_Uniform_Matrix mvpMatrix("mvpMatrix");
    return;
}