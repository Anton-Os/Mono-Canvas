#include "pipeline/GLSL_StateStream.hpp"

void GLSL_StateStream::set_mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(GLSL_StateStream::unifLoc[GLSL_StateStream::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void GLSL_StateStream::initUniforms(){
    GLSL_StateStream::unifLoc[GLSL_StateStream::mvpMatrix] = glGetUniformLocation(GLSL_StateStream::shaderProgID, "mvpMatrix");
    if(GLSL_StateStream::unifLoc[GLSL_StateStream::mvpMatrix] == -1) std::cout << "uniform mvpMatrix failed to initialize" << std::endl;
}