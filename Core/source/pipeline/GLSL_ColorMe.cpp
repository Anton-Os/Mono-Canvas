#include "pipeline/GLSL_ColorMe.hpp"

void GLSL_ColorMe::set_mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(GLSL_ColorMe::unifLoc[GLSL_ColorMe::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void GLSL_ColorMe::set_xMin(float xMin){
    glUniform1f(GLSL_ColorMe::unifLoc[GLSL_ColorMe::xMin], xMin);
}

void GLSL_ColorMe::set_xMax(float xMax){
    glUniform1f(GLSL_ColorMe::unifLoc[GLSL_ColorMe::xMax], xMax);
}

void GLSL_ColorMe::set_yMin(float yMin){
    glUniform1f(GLSL_ColorMe::unifLoc[GLSL_ColorMe::yMin], yMin);
}

void GLSL_ColorMe::set_yMax(float yMax){
    glUniform1f(GLSL_ColorMe::unifLoc[GLSL_ColorMe::yMax], yMax);
}

void GLSL_ColorMe::set_zMin(float zMin){
    glUniform1f(GLSL_ColorMe::unifLoc[GLSL_ColorMe::zMin], zMin);
}

void GLSL_ColorMe::set_zMax(float zMax){
    glUniform1f(GLSL_ColorMe::unifLoc[GLSL_ColorMe::zMax], zMax);
}

void GLSL_ColorMe::set_renderMode(GLuint renderMode){
    glUniform1ui(GLSL_ColorMe::unifLoc[GLSL_ColorMe::renderMode], renderMode);
}

void GLSL_ColorMe::initUniforms(){
    GLSL_ColorMe::unifLoc[GLSL_ColorMe::mvpMatrix] = glGetUniformLocation(GLSL_ColorMe::shaderProgID, "mvpMatrix");
    if(GLSL_ColorMe::unifLoc[GLSL_ColorMe::mvpMatrix] == -1) std::cout << "uniform mvpMatrix failed to initialize" << std::endl;
    GLSL_ColorMe::unifLoc[GLSL_ColorMe::renderMode] = glGetUniformLocation(GLSL_ColorMe::shaderProgID, "renderMode");
    if(GLSL_ColorMe::unifLoc[GLSL_ColorMe::renderMode] == -1) std::cout << "uniform renderMode failed to initialize" << std::endl;
    GLSL_ColorMe::unifLoc[GLSL_ColorMe::xMin] = glGetUniformLocation(GLSL_ColorMe::shaderProgID, "xMin");
    if(GLSL_ColorMe::unifLoc[GLSL_ColorMe::xMin] == -1) std::cout << "uniform xMin failed to initialize" << std::endl;
    GLSL_ColorMe::unifLoc[GLSL_ColorMe::xMax] = glGetUniformLocation(GLSL_ColorMe::shaderProgID, "xMax");
    if(GLSL_ColorMe::unifLoc[GLSL_ColorMe::xMax] == -1) std::cout << "uniform xMax failed to initialize" << std::endl;
    GLSL_ColorMe::unifLoc[GLSL_ColorMe::yMin] = glGetUniformLocation(GLSL_ColorMe::shaderProgID, "yMin");
    if(GLSL_ColorMe::unifLoc[GLSL_ColorMe::yMin] == -1) std::cout << "uniform yMin failed to initialize" << std::endl;
    GLSL_ColorMe::unifLoc[GLSL_ColorMe::yMax] = glGetUniformLocation(GLSL_ColorMe::shaderProgID, "yMax");
    if(GLSL_ColorMe::unifLoc[GLSL_ColorMe::yMax] == -1) std::cout << "uniform yMax failed to initialize" << std::endl;
    GLSL_ColorMe::unifLoc[GLSL_ColorMe::zMin] = glGetUniformLocation(GLSL_ColorMe::shaderProgID, "zMin");
    if(GLSL_ColorMe::unifLoc[GLSL_ColorMe::zMin] == -1) std::cout << "uniform zMin failed to initialize" << std::endl;
    GLSL_ColorMe::unifLoc[GLSL_ColorMe::zMax] = glGetUniformLocation(GLSL_ColorMe::shaderProgID, "zMax");
    if(GLSL_ColorMe::unifLoc[GLSL_ColorMe::zMax] == -1) std::cout << "uniform zMax failed to initialize" << std::endl;
}