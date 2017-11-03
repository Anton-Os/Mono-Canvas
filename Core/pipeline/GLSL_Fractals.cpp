#include "Pipeline.h"

void GLSL_Fractals::set_mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(GLSL_Fractals::unifLoc[GLSL_Fractals::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void GLSL_Fractals::set_iterCount(GLuint iterCount){
    glUniform1ui(GLSL_Fractals::unifLoc[GLSL_Fractals::iterCount], iterCount);
}

void GLSL_Fractals::initUniforms(){
    GLSL_Fractals::unifLoc[GLSL_Fractals::mvpMatrix] = glGetUniformLocation(GLSL_Fractals::shaderProgID, "mvpMatrix");
    if(GLSL_Fractals::unifLoc[GLSL_Fractals::mvpMatrix] == -1) std::cout << "uniform mvpMatrix failed to initialize" << std::endl;
    GLSL_Fractals::unifLoc[GLSL_Fractals::iterCount] = glGetUniformLocation(GLSL_Fractals::shaderProgID, "iterCount");
    if(GLSL_Fractals::unifLoc[GLSL_Fractals::iterCount] == -1) std::cout << "uniform iterCount failed to initialize" << std::endl;
}