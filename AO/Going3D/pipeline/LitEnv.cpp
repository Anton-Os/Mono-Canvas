
#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* void LitEnv::worldMatrix(litEnv_UniformData* Uniforms){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UniformIndex::worldMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->worldMatrix));
} */

void LitEnv::worldMatrix(glm::mat4 worldMatrix){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UNI::worldMatrix], 1, GL_FALSE, glm::value_ptr(worldMatrix));
}

/* void LitEnv::localMatrix(litEnv_UniformData* Uniforms){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UniformIndex::localMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->localMatrix));
} */

void LitEnv::localMatrix(glm::mat4 localMatrix){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UNI::localMatrix], 1, GL_FALSE, glm::value_ptr(localMatrix));
}

void LitEnv::cameraPos(std::array<GLfloat, 3> cameraPos){
    glUniform3fv(LitEnv::uniformLocation[LitEnv_UNI::cameraPos], 1, cameraPos.data());
}

void LitEnv::materialBlock(MaterialBlock* materialBlock){
	glGenBuffers(1, &LitEnv::SSBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, LitEnv::SSBO[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(MaterialBlock), materialBlock, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, LitEnv::SSBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void LitEnv::lightSourceBlock(LightSourceBlock* lightSourceBlock){
	glGenBuffers(1, &LitEnv::SSBO[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, LitEnv::SSBO[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(LightSourceBlock), lightSourceBlock, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, LitEnv::SSBO[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void LitEnv::setUniforms(litEnv_UniformData* Uniforms){
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "worldMatrix") );
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "localMatrix") );
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "cameraPos") );

    if(LitEnv::uniformLocation[LitEnv_UNI::worldMatrix] == -1) std::cerr << "LitEnv uniform error: worldMatrix" << std::endl; 
    if(LitEnv::uniformLocation[LitEnv_UNI::localMatrix] == -1) std::cerr << "LitEnv uniform error: localMatrix" << std::endl;
    if(LitEnv::uniformLocation[LitEnv_UNI::cameraPos] == -1) std::cerr << "LitEnv uniform error: cameraPos" << std::endl;

    LitEnv::worldMatrix(Uniforms->worldMatrix);
    LitEnv::localMatrix(Uniforms->localMatrix);
    LitEnv::cameraPos(Uniforms->cameraPos);
}

void LitEnv::setUniforms(litEnv_UniformData* Uniforms, ModelComposite* Model){
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "worldMatrix") );
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "localMatrix") );
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "cameraPos") );

    if(LitEnv::uniformLocation[LitEnv_UNI::worldMatrix] == -1) std::cerr << "LitEnv uniform error: worldMatrix" << std::endl; 
    if(LitEnv::uniformLocation[LitEnv_UNI::localMatrix] == -1) std::cerr << "LitEnv uniform error: localMatrix" << std::endl;
    if(LitEnv::uniformLocation[LitEnv_UNI::cameraPos] == -1) std::cerr << "LitEnv uniform error: cameraPos" << std::endl;

    LitEnv::worldMatrix(Uniforms->worldMatrix);
    LitEnv::localMatrix(Uniforms->localMatrix);
    LitEnv::cameraPos(Uniforms->cameraPos);
    LitEnv::materialBlock(&Model->materialBlock);

    LightSourceBlock lightSourceBlock = {
        100.0f,
        {0.0f, 0.0f, 0.0f}
    };
    LitEnv::lightSourceBlock(&lightSourceBlock);
}