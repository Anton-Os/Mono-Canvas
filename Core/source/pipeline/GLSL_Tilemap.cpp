#include "pipeline/GLSL_Tilemap.hpp"

void GLSL_Tilemap::set_mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(GLSL_Tilemap::unifLoc[GLSL_Tilemap::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void GLSL_Tilemap::set_state(GLint state){
    glUniform1i(GLSL_Tilemap::unifLoc[GLSL_Tilemap::state], state);
}

void GLSL_Tilemap::initUniforms(){
    GLSL_Tilemap::unifLoc[GLSL_Tilemap::mvpMatrix] = glGetUniformLocation(GLSL_Tilemap::shaderProgID, "mvpMatrix");
    if(GLSL_Tilemap::unifLoc[GLSL_Tilemap::mvpMatrix] == -1) std::cout << "uniform mvpMatrix failed to initialize" << std::endl;
    GLSL_Tilemap::unifLoc[GLSL_Tilemap::state] = glGetUniformLocation(GLSL_Tilemap::shaderProgID, "state");
    if(GLSL_Tilemap::unifLoc[GLSL_Tilemap::state] == -1) std::cout << "uniform state failed to initialize" << std::endl;
}