
#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void LitEnv::mvMatrix(glm::mat4 mvMatrix){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UNI::mvMatrix], 1, GL_FALSE, glm::value_ptr(mvMatrix));
}

void LitEnv::mvpMatrix(glm::mat4 mvpMatrix){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UNI::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void LitEnv::nMatrix(glm::mat3 nMatrix){
     glUniformMatrix3fv(LitEnv::uniformLocation[LitEnv_UNI::nMatrix], 1, GL_FALSE, glm::value_ptr(nMatrix));
}

void LitEnv::lightSourcePos(std::array<GLfloat, 3> lightSourcePos){
     glUniform3fv(LitEnv::uniformLocation[LitEnv_UNI::lightSourcePos], 1, lightSourcePos.data());
}

void LitEnv::materialBlock(MaterialBlock* materialBlock){
	glGenBuffers(1, &LitEnv::SSBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, LitEnv::SSBO[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(MaterialBlock), materialBlock, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, LitEnv::SSBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

/* void LitEnv::lightSourceBlock(LightSourceBlock* lightSourceBlock){
	glGenBuffers(1, &LitEnv::SSBO[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, LitEnv::SSBO[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(LightSourceBlock), lightSourceBlock, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, LitEnv::SSBO[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
} */

void LitEnv::setUniforms(){
    LitEnv::uniformLocation.push_back(glGetUniformLocation(LitEnv::shaderProgID, "mvMatrix"));
    LitEnv::uniformLocation.push_back(glGetUniformLocation(LitEnv::shaderProgID, "mvpMatrix"));
    LitEnv::uniformLocation.push_back(glGetUniformLocation(LitEnv::shaderProgID, "nMatrix"));
    LitEnv::uniformLocation.push_back(glGetUniformLocation(LitEnv::shaderProgID, "lightSourcePos"));

    if(LitEnv::uniformLocation[LitEnv_UNI::mvMatrix] == -1) std::cerr << "LitEnv uniform error: mvMatrix" << std::endl; 
    if(LitEnv::uniformLocation[LitEnv_UNI::mvpMatrix] == -1) std::cerr << "LitEnv uniform error: mvpMatrix" << std::endl;
    if(LitEnv::uniformLocation[LitEnv_UNI::nMatrix] == -1) std::cerr << "LitEnv uniform error: nMatrix" << std::endl;
    if(LitEnv::uniformLocation[LitEnv_UNI::lightSourcePos] == -1) std::cerr << "LitEnv uniform error: lightSourcePos" << std::endl;
}