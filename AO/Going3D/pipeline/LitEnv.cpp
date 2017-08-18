
#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void LitEnv::worldMatrix(litEnv_UniformData* Uniforms){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UniformIndex::worldMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->worldMatrix));
}

void LitEnv::localMatrix(litEnv_UniformData* Uniforms){
     glUniformMatrix4fv(LitEnv::uniformLocation[LitEnv_UniformIndex::localMatrix], 1, GL_FALSE, glm::value_ptr(Uniforms->localMatrix));
}

void LitEnv::materialBlock(litEnv_UniformData* Uniforms, MaterialBlock* materialBlock){
    glUniformBlockBinding(LitEnv::shaderProgID, LitEnv::uniformLocation[LitEnv_UniformIndex::materialBlock], 1);

    glGenBuffers(1, &LitEnv::UBO[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, LitEnv::UBO[0]);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialBlock), &materialBlock, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, LitEnv::UBO[0]);
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
    LitEnv::uniformLocation.push_back( glGetUniformBlockIndex(LitEnv::shaderProgID, "materialBlock") );

    if(LitEnv::uniformLocation[LitEnv_UniformIndex::worldMatrix] == -1) std::cerr << "LitEnv uniform error: worldMatrix" << std::endl; 
    if(LitEnv::uniformLocation[LitEnv_UniformIndex::localMatrix] == -1) std::cerr << "localMatrix" << std::endl;
    if(LitEnv::uniformLocation[LitEnv_UniformIndex::materialBlock] == -1) std::cerr << "materialBlock" << std::endl;

    LitEnv::worldMatrix(Uniforms);
    LitEnv::localMatrix(Uniforms);
    LitEnv::materialBlock(Uniforms, &Model->materialBlock);
}