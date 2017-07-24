
#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void viewer3D_UniformBlocks(viewer3D_ShaderObj* ShaderObj, ModelStatic* Model){
	GLuint vert_uniformBlockID = glGetUniformBlockIndex(ShaderObj->shaderProgID, "vertexBlock");
	GLuint frag_uniformBlockID = glGetUniformBlockIndex(ShaderObj->shaderProgID, "fragmentBlock");

	if(vert_uniformBlockID == GL_INVALID_INDEX) 
	std::cerr << "Uniform block 'vertexBlock' does not exist in vertex shader" << std::endl;

	if(frag_uniformBlockID == GL_INVALID_INDEX) 
	std::cerr << "Uniform block 'fragmentBlock' does not exist in fragment shader" << std::endl;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 200.f);
	glm::mat4 view = glm::mat4(1);

	glm::mat4 worldMatrix = projection * view;
	glm::mat4 localMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, -5.0f));

    GLfloat ambientLightStrength = 1.0f;
	GLuint surfaceRenderMode;

    if(Model->renderParams[ShaderCtrlBit::color] == 1 && Model->renderParams[ShaderCtrlBit::texCoord] == 0){
		std::cout << "No vertex colors present, texture coordinates are" << std::endl;
		surfaceRenderMode = 0;
	} else {
		std::cerr << "We are in a caveman era" << std::endl;
		return;
	}

	ShaderObj->vert_uniformData = {
		worldMatrix,
		localMatrix
	};

	ShaderObj->frag_uniformData = {
		ambientLightStrength,
		surfaceRenderMode
	};

	glUniformBlockBinding(vert_uniformBlockID, ShaderObj->shaderProgID, 0);
	glUniformBlockBinding(frag_uniformBlockID, ShaderObj->shaderProgID, 1);

	GLuint UBO[2];
	glGenBuffers(2, UBO);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO[0]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ShaderObj->vert_uniformData), &ShaderObj->vert_uniformData, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO[0]);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO[1]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ShaderObj->frag_uniformData), &ShaderObj->frag_uniformData, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, UBO[1]);
}