
#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void LitEnv::worldMatrix(litEnv_UniformData* Uniforms){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UniformIndex::worldMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->worldMatrix));
}

void LitEnv::localMatrix(litEnv_UniformData* Uniforms){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UniformIndex::localMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->localMatrix));
}

void LitEnv::testBlock(litEnv_UniformData* Uniforms, TestBlock* testBlock){
	glGenBuffers(1, &LitEnv::UBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, LitEnv::UBO[0]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(TestBlock), &testBlock, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, LitEnv::UBO[0]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void LitEnv::materialBlock(litEnv_UniformData* Uniforms, MaterialBlock* materialBlock){
	glGenBuffers(1, &LitEnv::UBO[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, LitEnv::UBO[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(MaterialBlock), materialBlock, GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, LitEnv::UBO[1]);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void LitEnv::setUniforms(litEnv_UniformData* Uniforms){
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "worldMatrix") );
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "localMatrix") );

    if(LitEnv::uniformLocation[LitEnv_UniformIndex::worldMatrix] == -1) std::cerr << "worldMatrix has not been set properly" << std::endl; 
    if(LitEnv::uniformLocation[LitEnv_UniformIndex::localMatrix] == -1) std::cerr << "localMatrix has not been set properly" << std::endl;

    LitEnv::worldMatrix(Uniforms);
    LitEnv::localMatrix(Uniforms);
}

void LitEnv::setUniforms(litEnv_UniformData* Uniforms, ModelComposite* Model){
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "worldMatrix") );
    LitEnv::uniformLocation.push_back( glGetUniformLocation(LitEnv::shaderProgID, "localMatrix") );

    if(LitEnv::uniformLocation[LitEnv_UniformIndex::worldMatrix] == -1) std::cerr << "LitEnv uniform error: worldMatrix" << std::endl; 
    if(LitEnv::uniformLocation[LitEnv_UniformIndex::localMatrix] == -1) std::cerr << "LitEnv uniform error: localMatrix" << std::endl;

    LitEnv::worldMatrix(Uniforms);
    LitEnv::localMatrix(Uniforms);
    // TestBlock test123 = { 0.4f, 0.3f, 0.1f };
    // LitEnv::testBlock(Uniforms, &test123);
    MaterialBlock materialTest = {{0.5f, 0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f, 0.5f}};
    LitEnv::materialBlock(Uniforms, &materialTest);
}