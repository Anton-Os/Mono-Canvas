#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void CamFlash::mvMatrix(glm::mat4 mvMatrix){
    glUniformMatrix4fv(CamFlash::unifLoc[CF_UNIF::mvMatrix], 1, GL_FALSE, glm::value_ptr(mvMatrix));
}

void CamFlash::mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(CamFlash::unifLoc[CF_UNIF::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void CamFlash::nMatrix(glm::mat3 nMatrix){
    glUniformMatrix4fv(CamFlash::unifLoc[CF_UNIF::nMatrix], 1, GL_FALSE, glm::value_ptr(nMatrix));
}

void CamFlash::materialBlock(MaterialBlock* materialBlock){
	glGenBuffers(1, &CamFlash::SSBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, CamFlash::SSBO[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(MaterialBlock), materialBlock, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, CamFlash::SSBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void CamFlash::initUniforms(){
    CamFlash::unifLoc[CF_UNIF::mvMatrix] = glGetUniformLocation(CamFlash::shaderProgID, "mvMatrix");
    if(CamFlash::unifLoc[CF_UNIF::mvMatrix] == -1) std::cerr << "CamFlash uniform issue: mvMatrix" << std::endl;
    CamFlash::unifLoc[CF_UNIF::mvpMatrix] = glGetUniformLocation(CamFlash::shaderProgID, "mvpMatrix");
    if(CamFlash::unifLoc[CF_UNIF::mvpMatrix] == -1) std::cerr << "CamFlash uniform issue: mvpMatrix" << std::endl;
    CamFlash::unifLoc[CF_UNIF::nMatrix] = glGetUniformLocation(CamFlash::shaderProgID, "nMatrix");
    if(CamFlash::unifLoc[CF_UNIF::nMatrix] == -1) std::cerr << "CamFlash uniform issue: nMatrix" << std::endl;
}