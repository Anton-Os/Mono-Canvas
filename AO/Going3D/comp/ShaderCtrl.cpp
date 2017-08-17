
#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void NoBlocks::worldMatrix(noBlocks_UniformData* Uniforms){
    glUniformMatrix4fv(NoBlocks::uniformLocation[NoBlocks_UniformIndex::worldMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->worldMatrix));
}

void NoBlocks::localMatrix(noBlocks_UniformData* Uniforms){
    glUniformMatrix4fv(NoBlocks::uniformLocation[NoBlocks_UniformIndex::localMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->localMatrix));
}

void NoBlocks::defaultColor(noBlocks_UniformData* Uniforms){
    glUniform4fv(NoBlocks::uniformLocation[NoBlocks_UniformIndex::defaultColor], 1, Uniforms->defaultColor.data());
}

void NoBlocks::surfaceRenderMode(noBlocks_UniformData* Uniforms){
	glUniform1ui(NoBlocks::uniformLocation[NoBlocks_UniformIndex::surfaceRenderMode], Uniforms->surfaceRenderMode);
}

void NoBlocks::setUniforms(noBlocks_UniformData* Uniforms){
	NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "worldMatrix") );
	NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "localMatrix") );
    NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "defaultColor") );
	NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "surfaceRenderMode") );

    if(NoBlocks::uniformLocation[NoBlocks_UniformIndex::worldMatrix] == -1) std::cerr << "worldMatrix has not been set properly" << std::endl; 
	if(NoBlocks::uniformLocation[NoBlocks_UniformIndex::localMatrix] == -1) std::cerr << "localMatrix has not been set properly" << std::endl;
	if(NoBlocks::uniformLocation[NoBlocks_UniformIndex::defaultColor] == -1) std::cerr << "defaultColor has not been set properly" << std::endl;
	if(NoBlocks::uniformLocation[NoBlocks_UniformIndex::surfaceRenderMode] == -1) std::cerr << "surfaceRenderMode has not been set properly" << std::endl; 

    NoBlocks::worldMatrix(Uniforms);
    NoBlocks::localMatrix(Uniforms);
    NoBlocks::defaultColor(Uniforms);
    NoBlocks::surfaceRenderMode(Uniforms);
}

// LitEnv Shader Program

void LitEnv::worldMatrix(litEnv_UniformData* Uniforms){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UniformIndex::worldMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->worldMatrix));
}

void LitEnv::localMatrix(litEnv_UniformData* Uniforms){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UniformIndex::localMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->localMatrix));
}

void LitEnv::setUniforms(litEnv_UniformData* Uniforms){
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "worldMatrix") );
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "localMatrix") );

    if(LitEnv::uniformLocation[LitEnv_UniformIndex::worldMatrix] == -1) std::cerr << "worldMatrix has not been set properly" << std::endl; 
    if(LitEnv::uniformLocation[LitEnv_UniformIndex::localMatrix] == -1) std::cerr << "localMatrix has not been set properly" << std::endl;

    LitEnv::worldMatrix(Uniforms);
    LitEnv::localMatrix(Uniforms);
}