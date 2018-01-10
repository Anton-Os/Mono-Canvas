#include <iostream>

#include "Loaders.h"
#include "loaders/CompShaders.hpp"

int main(int argc, char** argv) {
    std::string parentDir = getParentDirectory(argv[0]);
    Comp_VertexShader vertexShader;
    Comp_FragmentShader fragmentShader;
    Comp_ShaderProg shaderProg(&vertexShader, &fragmentShader);
    return 0;
}
