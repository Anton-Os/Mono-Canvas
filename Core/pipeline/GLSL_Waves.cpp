#include "Pipeline.h"

void GLSL_Waves::set_mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(GLSL_Waves::unifLoc[GLSL_Waves::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void GLSL_Waves::set_renderMode(GLuint renderMode){
    glUniform1ui(GLSL_Waves::unifLoc[GLSL_Waves::renderMode], renderMode);
}

void GLSL_Waves::set_primMode(GLuint primMode){
    glUniform1ui(GLSL_Waves::unifLoc[GLSL_Waves::primMode], primMode);
}

void GLSL_Waves::set_waveHeight(GLfloat waveHeight){
    glUniform1f(GLSL_Waves::unifLoc[GLSL_Waves::waveHeight], waveHeight);
}

void GLSL_Waves::set_waveInc(GLfloat waveInc){
    glUniform1f(GLSL_Waves::unifLoc[GLSL_Waves::waveInc], waveInc);
}

void GLSL_Waves::initUniforms(){
    GLSL_Waves::unifLoc[GLSL_Waves::mvpMatrix] = glGetUniformLocation(GLSL_Waves::shaderProgID, "mvpMatrix");
    if(GLSL_Waves::unifLoc[GLSL_Waves::mvpMatrix] == -1) std::cout << "uniform mvpMatrix failed to initialize" << std::endl;
    GLSL_Waves::unifLoc[GLSL_Waves::renderMode] = glGetUniformLocation(GLSL_Waves::shaderProgID, "renderMode");
    if(GLSL_Waves::unifLoc[GLSL_Waves::renderMode] == -1) std::cout << "uniform renderMode failed to initialize" << std::endl;
    GLSL_Waves::unifLoc[GLSL_Waves::primMode] = glGetUniformLocation(GLSL_Waves::shaderProgID, "primMode");
    if(GLSL_Waves::unifLoc[GLSL_Waves::primMode] == -1) std::cout << "uniform primMode failed to initialize" << std::endl;
    GLSL_Waves::unifLoc[GLSL_Waves::waveHeight] = glGetUniformLocation(GLSL_Waves::shaderProgID, "waveHeight");
    if(GLSL_Waves::unifLoc[GLSL_Waves::waveHeight] == -1) std::cout << "uniform waveHeight failed to initialize" << std::endl;
    GLSL_Waves::unifLoc[GLSL_Waves::waveInc] = glGetUniformLocation(GLSL_Waves::shaderProgID, "waveInc");
    if(GLSL_Waves::unifLoc[GLSL_Waves::waveInc] == -1) std::cout << "uniform waveInc failed to initialize" << std::endl;
}