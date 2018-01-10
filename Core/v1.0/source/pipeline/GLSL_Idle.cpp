#include "pipeline/GLSL_Idle.hpp"

void GLSL_Idle::set_mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(GLSL_Idle::unifLoc[GLSL_Idle::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void GLSL_Idle::set_renderMode(GLuint renderMode){
    glUniform1ui(GLSL_Idle::unifLoc[GLSL_Idle::renderMode], renderMode);
}

void GLSL_Idle::initUniforms(){
    GLSL_Idle::unifLoc[GLSL_Idle::mvpMatrix] = glGetUniformLocation(GLSL_Idle::shaderProgID, "mvpMatrix");
    if(GLSL_Idle::unifLoc[GLSL_Idle::mvpMatrix] == -1) std::cout << "uniform mvpMatrix failed to initialize" << std::endl;
    GLSL_Idle::unifLoc[GLSL_Idle::renderMode] = glGetUniformLocation(GLSL_Idle::shaderProgID, "renderMode");
    if(GLSL_Idle::unifLoc[GLSL_Idle::renderMode] == -1) std::cout << "uniform renderMode failed to initialize" << std::endl;
}