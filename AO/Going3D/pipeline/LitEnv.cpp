#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void LitEnv::mvMatrix(glm::mat4 mvMatrix){
    glUniformMatrix4fv(LitEnv::unifLoc[LE_UNIF::mvMatrix], 1, GL_FALSE, glm::value_ptr(mvMatrix));
}

void LitEnv::mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(LitEnv::unifLoc[LE_UNIF::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void LitEnv::nMatrix(glm::mat3 nMatrix){
    glUniformMatrix3fv(LitEnv::unifLoc[LE_UNIF::nMatrix], 1, GL_FALSE, glm::value_ptr(nMatrix));
}

void LitEnv::materialBlock(MaterialBlock* materialBlock){
	glGenBuffers(1, &LitEnv::SSBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, LitEnv::SSBO[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(MaterialBlock), materialBlock, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, LitEnv::SSBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void LitEnv::initUniforms(){
    LitEnv::unifLoc[LE_UNIF::mvMatrix] = glGetUniformLocation(LitEnv::shaderProgID, "mvMatrix");
    if(LitEnv::unifLoc[LE_UNIF::mvMatrix] == -1) std::cerr << "LitEnv uniform issue: mvMatrix" << std::endl;
    LitEnv::unifLoc[LE_UNIF::mvpMatrix] = glGetUniformLocation(LitEnv::shaderProgID, "mvpMatrix");
    if(LitEnv::unifLoc[LE_UNIF::mvpMatrix] == -1) std::cerr << "LitEnv uniform issue: mvpMatrix" << std::endl;
    LitEnv::unifLoc[LE_UNIF::nMatrix] = glGetUniformLocation(LitEnv::shaderProgID, "nMatrix");
    if(LitEnv::unifLoc[LE_UNIF::nMatrix] == -1) std::cerr << "LitEnv uniform issue: nMatrix" << std::endl;
}