#include "pipeline/GL4_Shader_Factory.hpp"

static char error_stageDuplicate[] = "Attempting to create a stage duplicate";
static char error_shaderIncomplete[] = "Incomplete information passed to shader stage";

void GL4_Shader_Factory::add_shader(GL4_Shader* shader){
    if(!match_stage(shader->get_stage(), &shaders)) logError(__FILE__, __LINE__, error_stageDuplicate);
    if(!shader->get_ready()) logError(__FILE__, __LINE__, error_shaderIncomplete);

    shaders.push_back(*shader);
}

static bool match_stage(GL4_Shader_Stage::Pick stage, std::vector<GL4_Shader>* shadersArg){
    if(shadersArg->empty()) return true;

    for(unsigned shaderElem = 0; shaderElem < shadersArg->size(); shaderElem)
        if(shadersArg->at(shaderElem).get_stage() == stage) return false;
    
    return true;
}