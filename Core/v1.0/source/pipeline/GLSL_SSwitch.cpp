#include "pipeline/GLSL_SSwitch.hpp"

void GLSL_SSwitch::set_mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(GLSL_SSwitch::unifLoc[GLSL_SSwitch::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void GLSL_SSwitch::set_state(GLint state){
    glUniform1i(GLSL_SSwitch::unifLoc[GLSL_SSwitch::state], state);
}

void GLSL_SSwitch::initUniforms(){
    GLSL_SSwitch::unifLoc[GLSL_SSwitch::mvpMatrix] = glGetUniformLocation(GLSL_SSwitch::shaderProgID, "mvpMatrix");
    if(GLSL_SSwitch::unifLoc[GLSL_SSwitch::mvpMatrix] == -1) std::cout << "uniform mvpMatrix failed to initialize" << std::endl;
    GLSL_SSwitch::unifLoc[GLSL_SSwitch::state] = glGetUniformLocation(GLSL_SSwitch::shaderProgID, "state");
    if(GLSL_SSwitch::unifLoc[GLSL_SSwitch::state] == -1) std::cout << "uniform state failed to initialize" << std::endl;
}