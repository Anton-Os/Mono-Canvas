
#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLint noBlocks_worldMatrix(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms){
    GLint locationIndex = glGetUniformLocation(shaderProgID, "worldMatrix");
    glUniformMatrix4fv(locationIndex, 1, GL_FALSE, glm::value_ptr(noBlocks_Uniforms->worldMatrix));
    return locationIndex;
}

GLint noBlocks_localMatrix(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms){
    GLint locationIndex = glGetUniformLocation(shaderProgID, "localMatrix");
    glUniformMatrix4fv(locationIndex, 1, GL_FALSE, glm::value_ptr(noBlocks_Uniforms->localMatrix));
	return locationIndex;
}

GLint noBlocks_defaultColor(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms){
	GLint locationIndex = glGetUniformLocation(shaderProgID, "defaultColor");
    glUniform4fv(locationIndex, 1, noBlocks_Uniforms->defaultColor.data());
	return locationIndex;
}

GLint noBlocks_surfaceRenderMode(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms){
	GLint locationIndex = glGetUniformLocation(shaderProgID, "surfaceRenderMode");
	glUniform1ui(locationIndex, noBlocks_Uniforms->surfaceRenderMode);
	return locationIndex;
}

int noBlocks_setUniforms(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms){
	GLint worldMatrix_INDEX = noBlocks_worldMatrix(shaderProgID, noBlocks_Uniforms);
	GLint localMatrix_INDEX = noBlocks_localMatrix(shaderProgID, noBlocks_Uniforms);
    GLint defaultColor_INDEX = noBlocks_defaultColor(shaderProgID, noBlocks_Uniforms);
	GLint surfaceRenderMode_INDEX = noBlocks_surfaceRenderMode(shaderProgID, noBlocks_Uniforms);

    if(worldMatrix_INDEX == -1) std::cerr << "worldMatrix has not been set properly" << std::endl; 
	if(localMatrix_INDEX == -1) std::cerr << "localMatrix has not been set properly" << std::endl;
	if(defaultColor_INDEX == -1) std::cerr << "defaultColor has not been set properly" << std::endl;
	if(surfaceRenderMode_INDEX == -1) std::cerr << "surfaceRenderMode has not been set properly" << std::endl; 

	return 0;
}

int noBlocks_setUniforms(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms, ModelStatic* Model){

    noBlocks_Uniforms->worldMatrix = glm::mat4(1);
    noBlocks_Uniforms->localMatrix = glm::mat4(1);

    noBlocks_Uniforms->defaultColor = {0.2588f, 0.5254f, 0.9568f, 0.8f};

    if(Model->renderParams[ShaderCtrlBit::color] == 1 && Model->renderParams[ShaderCtrlBit::texCoord] == 0){
        std::cout << "No vertex colors present, texture coordinates are" << std::endl;
        noBlocks_Uniforms->surfaceRenderMode = 1;
     } else {
        std::cerr << "We are in a caveman era" << std::endl;
        return -1;
     }


    GLint worldMatrix_INDEX = noBlocks_worldMatrix(shaderProgID, noBlocks_Uniforms);
    GLint localMatrix_INDEX = noBlocks_localMatrix(shaderProgID, noBlocks_Uniforms);
    GLint defaultColor_INDEX = noBlocks_defaultColor(shaderProgID, noBlocks_Uniforms);
    GLint surfaceRenderMode_INDEX = noBlocks_surfaceRenderMode(shaderProgID, noBlocks_Uniforms);

    if(worldMatrix_INDEX == -1) std::cerr << "worldMatrix has not been set properly" << std::endl;
    if(localMatrix_INDEX == -1) std::cerr << "localMatrix has not been set properly" << std::endl;
    if(defaultColor_INDEX == -1) std::cerr << "defaultColor has not been set properly" << std::endl;
    if(surfaceRenderMode_INDEX == -1) std::cerr << "surfaceRenderMode has not been set properly" << std::endl;

    return 0;
}
