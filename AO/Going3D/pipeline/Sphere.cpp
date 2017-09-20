#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Sphere::mvpMatrix(glm::mat4 mvpMatrix){
    glUniformMatrix4fv(Sphere::unifLoc[SPH_UNIF::mvpMatrix], 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void Sphere::nMatrix(glm::mat3 nMatrix){
    glUniformMatrix3fv(Sphere::unifLoc[SPH_UNIF::nMatrix], 1, GL_FALSE, glm::value_ptr(nMatrix));
}

void Sphere::renderMode(GLuint renderMode){
    glUniform1ui(Sphere::unifLoc[SPH_UNIF::renderMode], renderMode);
}

void Sphere::sphereParams(std::array<GLuint, 2> sphereParams){
    glUniform2uiv(Sphere::unifLoc[SPH_UNIF::sphereParams], 1, sphereParams.data());
}

void Sphere::gradient(std::array<GLfloat, 6> gradient){
    glUniform3fv(Sphere::unifLoc[SPH_UNIF::gradient], 1, gradient.data());
}

void Sphere::colorPalette(ColorPalette4x3* colorPalette){
	glGenBuffers(1, &Sphere::SSBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, Sphere::SSBO[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(ColorPalette4x3), colorPalette, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, Sphere::SSBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void Sphere::initUniforms(){
    Sphere::unifLoc[SPH_UNIF::mvpMatrix] = glGetUniformLocation(Sphere::shaderProgID, "mvpMatrix");
    if(Sphere::unifLoc[SPH_UNIF::mvpMatrix] == -1) std::cerr << "Sphere uniform issue: mvpMatrix" << std::endl;
    Sphere::unifLoc[SPH_UNIF::nMatrix] = glGetUniformLocation(Sphere::shaderProgID, "nMatrix");
    if(Sphere::unifLoc[SPH_UNIF::nMatrix] == -1) std::cerr << "Sphere uniform issue: nMatrix" << std::endl;
    Sphere::unifLoc[SPH_UNIF::renderMode] = glGetUniformLocation(Sphere::shaderProgID, "renderMode");
    if(Sphere::unifLoc[SPH_UNIF::renderMode] == -1) std::cerr << "Sphere uniform issue: renderMode" << std::endl;
    Sphere::unifLoc[SPH_UNIF::sphereParams] = glGetUniformLocation(Sphere::shaderProgID, "sphereParams");
    if(Sphere::unifLoc[SPH_UNIF::sphereParams] == -1) std::cerr << "Sphere uniform issue: sphereParams" << std::endl;
    Sphere::unifLoc[SPH_UNIF::gradient] = glGetUniformLocation(Sphere::shaderProgID, "gradient");
    if(Sphere::unifLoc[SPH_UNIF::gradient] == -1) std::cerr << "Sphere uniform issue: gradient" << std::endl;
}