
#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void NoBlocks::worldMatrix(noBlocks_UniformData* Uniforms){
    glUniformMatrix4fv(NoBlocks::uniformLocation[UniformIndex::worldMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->worldMatrix));
}

void NoBlocks::localMatrix(noBlocks_UniformData* Uniforms){
    glUniformMatrix4fv(NoBlocks::uniformLocation[UniformIndex::localMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->localMatrix));
}

void NoBlocks::defaultColor(noBlocks_UniformData* Uniforms){
    glUniform4fv(NoBlocks::uniformLocation[UniformIndex::defaultColor], 1, Uniforms->defaultColor.data());
}

void NoBlocks::surfaceRenderMode(noBlocks_UniformData* Uniforms){
	glUniform1ui(NoBlocks::uniformLocation[UniformIndex::surfaceRenderMode], Uniforms->surfaceRenderMode);
}

void NoBlocks::setUniforms(noBlocks_UniformData* Uniforms){
	NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "worldMatrix") );
	NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "localMatrix") );
    NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "defaultColor") );
	NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "surfaceRenderMode") );

    if(NoBlocks::uniformLocation[UniformIndex::worldMatrix] == -1) std::cerr << "worldMatrix has not been set properly" << std::endl; 
	if(NoBlocks::uniformLocation[UniformIndex::localMatrix] == -1) std::cerr << "localMatrix has not been set properly" << std::endl;
	if(NoBlocks::uniformLocation[UniformIndex::defaultColor] == -1) std::cerr << "defaultColor has not been set properly" << std::endl;
	if(NoBlocks::uniformLocation[UniformIndex::surfaceRenderMode] == -1) std::cerr << "surfaceRenderMode has not been set properly" << std::endl; 

    NoBlocks::worldMatrix(Uniforms);
    NoBlocks::localMatrix(Uniforms);
    NoBlocks::defaultColor(Uniforms);
    NoBlocks::surfaceRenderMode(Uniforms);
}

void NoBlocks::setUniforms(noBlocks_UniformData* Uniforms, ModelStatic* Model){
    Uniforms->worldMatrix = glm::mat4(1);
    Uniforms->localMatrix = glm::mat4(1);

    Uniforms->defaultColor = {0.2588f, 0.5254f, 0.9568f, 0.8f};

    if(Model->renderParams[ShaderCtrlBit::color] == 1 && Model->renderParams[ShaderCtrlBit::texCoord] == 0){
        std::cout << "No vertex colors present, texture coordinates are" << std::endl;
        Uniforms->surfaceRenderMode = 1;
     } else {
        std::cerr << "We are in a caveman era" << std::endl;
     }

	NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "worldMatrix") );
	NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "localMatrix") );
    NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "defaultColor") );
	NoBlocks::uniformLocation.push_back( glGetUniformLocation(NoBlocks::shaderProgID, "surfaceRenderMode") );

    if(NoBlocks::uniformLocation[UniformIndex::worldMatrix] == -1) std::cerr << "worldMatrix has not been set properly" << std::endl; 
	if(NoBlocks::uniformLocation[UniformIndex::localMatrix] == -1) std::cerr << "localMatrix has not been set properly" << std::endl;
	if(NoBlocks::uniformLocation[UniformIndex::defaultColor] == -1) std::cerr << "defaultColor has not been set properly" << std::endl;
	if(NoBlocks::uniformLocation[UniformIndex::surfaceRenderMode] == -1) std::cerr << "surfaceRenderMode has not been set properly" << std::endl; 

    NoBlocks::worldMatrix(Uniforms);
    NoBlocks::localMatrix(Uniforms);
    NoBlocks::defaultColor(Uniforms);
    NoBlocks::surfaceRenderMode(Uniforms);
}