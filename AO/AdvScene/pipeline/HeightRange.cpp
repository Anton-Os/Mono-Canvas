#include "Pipeline.h"

void GLSL_HeightRange::set_mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(GLSL_HeightRange::unifLoc[GLSL_HeightRange::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void GLSL_HeightRange::set_heightRange(GLfloat min, GLfloat max){
    glUniform2f(GLSL_HeightRange::unifLoc[GLSL_HeightRange::heightRange], min, max);
}

void GLSL_HeightRange::set_rise(GLfloat rise){
    glUniform1f(GLSL_HeightRange::unifLoc[GLSL_HeightRange::rise], rise);
}

void GLSL_HeightRange::set_renderMode(GLuint renderMode){
    glUniform1ui(GLSL_HeightRange::unifLoc[GLSL_HeightRange::renderMode], renderMode);
}

void GLSL_HeightRange::initUniforms(){
    GLSL_HeightRange::unifLoc[GLSL_HeightRange::mvpMatrix] = glGetUniformLocation(GLSL_HeightRange::shaderProgID, "mvpMatrix");
    if(GLSL_HeightRange::unifLoc[GLSL_HeightRange::mvpMatrix] == -1) std::cout << "uniform mvpMatrix failed to initialize" << std::endl;
    GLSL_HeightRange::unifLoc[GLSL_HeightRange::heightRange] = glGetUniformLocation(GLSL_HeightRange::shaderProgID, "heightRange");
    if(GLSL_HeightRange::unifLoc[GLSL_HeightRange::heightRange] == -1) std::cout << "uniform heightRange failed to initialize" << std::endl;
    GLSL_HeightRange::unifLoc[GLSL_HeightRange::rise] = glGetUniformLocation(GLSL_HeightRange::shaderProgID, "rise");
    if(GLSL_HeightRange::unifLoc[GLSL_HeightRange::rise] == -1) std::cout << "uniform rise failed to initialize" << std::endl;
    GLSL_HeightRange::unifLoc[GLSL_HeightRange::renderMode] = glGetUniformLocation(GLSL_HeightRange::shaderProgID, "renderMode");
    if(GLSL_HeightRange::unifLoc[GLSL_HeightRange::renderMode] == -1) std::cout << "uniform renderMode failed to initialize" << std::endl;

}