#include "Pipeline.h"

void GLSL_Flatscape::set_mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(GLSL_Flatscape::unifLoc[GLSL_Flatscape::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void GLSL_Flatscape::set_renderMode(GLuint renderMode){
    glUniform1ui(GLSL_Flatscape::unifLoc[GLSL_Flatscape::renderMode], renderMode);
}

void GLSL_Flatscape::initUniforms(){
    GLSL_Flatscape::unifLoc[GLSL_Flatscape::mvpMatrix] = glGetUniformLocation(GLSL_Flatscape::shaderProgID, "mvpMatrix");
    if(GLSL_Flatscape::unifLoc[GLSL_Flatscape::mvpMatrix] == -1) std::cout << "uniform mvpMatrix failed to initialize" << std::endl;
    GLSL_Flatscape::unifLoc[GLSL_Flatscape::renderMode] = glGetUniformLocation(GLSL_Flatscape::shaderProgID, "renderMode");
    if(GLSL_Flatscape::unifLoc[GLSL_Flatscape::renderMode] == -1) std::cout << "uniform renderMode failed to initialize" << std::endl;
}