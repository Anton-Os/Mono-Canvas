#include "loaders/CompShaders.hpp"

void Comp_ShaderProg::create() {
    std::string vertexShaderSource;
    // vertex shader creation phase
    writeFile(Comp_ShaderProg::vertexShader.name + ".vert", vertexShaderSource);
    std::string fragmentShaderSource;
    // vertex shader creation phase
    writeFile(Comp_ShaderProg::fragmentShader.name + ".frag", fragmentShaderSource);
}