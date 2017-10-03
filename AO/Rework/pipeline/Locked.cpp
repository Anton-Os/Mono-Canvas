#include "PipelineCtrl.h"

void Locked::mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(Locked::unifLoc[LK_UNIF::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void Locked::msTimer(std::array<GLuint, 2> msTimer){
    glUniform2uiv(Locked::unifLoc[LK_UNIF::msTimer], 1, msTimer.data());
}

void Locked::initUniforms(){
    Locked::unifLoc[LK_UNIF::mvpMatrix] = glGetUniformLocation(Locked::shaderProgID, "mvpMatrix");
    if(Locked::unifLoc[LK_UNIF::mvpMatrix] == -1) std::cout << "uniform mvpMatrix failed to initialize" << std::endl;
    Locked::unifLoc[LK_UNIF::msTimer] = glGetUniformLocation(Locked::shaderProgID, "msTimer");
    if(Locked::unifLoc[LK_UNIF::msTimer] == -1) std::cout << "uniform msTimer failed to initialize" << std::endl;
}