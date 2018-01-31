#include "pipeline/GL4_Program.hpp"

static char error_shadersEmpty[] = "No shaders are attributed to this program";
static char error_shadersLots[] = "You cannot hold over 8 shaders in a single program";
static char error_stageDuplicates[] = "Duplicates of shader stages detected!";
static char error_incompleteVF[] = "Incomplete pipeline, vertex and fragment shader necissary";
static char error_linkage[] = "Shader program failed to link";

static void detect_duplicates(std::bitset<6>* stageBits, std::vector<GL4_Shader>* shaders_arg){
    for(unsigned shaderElem = 0; shaderElem < shaders_arg->size(); shaderElem++){
        if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::vert){
            if(!stageBits->test(_GL4_Shader_Stage::vert)) stageBits->set(_GL4_Shader_Stage::vert);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        } else if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::frag){
            if(!stageBits->test(_GL4_Shader_Stage::frag)) stageBits->set(_GL4_Shader_Stage::frag);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        } else if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::tesc){
            if(!stageBits->test(_GL4_Shader_Stage::tesc)) stageBits->set(_GL4_Shader_Stage::tesc);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        } else if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::tese){
            if(!stageBits->test(_GL4_Shader_Stage::tese)) stageBits->set(_GL4_Shader_Stage::tese);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        } else if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::geom){
            if(!stageBits->test(_GL4_Shader_Stage::geom)) stageBits->set(_GL4_Shader_Stage::geom);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        } else if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::comp){
            if(!stageBits->test(_GL4_Shader_Stage::comp)) stageBits->set(_GL4_Shader_Stage::comp);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        }
    }
}

void GL4_Program::add_shader(GL4_Shader* shader_arg) {
    if(shaders.size() > 8) logError(__FILE__, __LINE__, error_shadersLots);
    shaders.push_back(*shader_arg);
    return;
}

void GL4_Program::create(){
    if(shaders.empty()) logError(__FILE__, __LINE__, error_shadersEmpty);
    detect_duplicates(&stageBits, &shaders);
    if(!stageBits.test(_GL4_Shader_Stage::vert) || !stageBits.test(_GL4_Shader_Stage::frag)) logError(__FILE__, __LINE__, error_incompleteVF);

    progID = glCreateProgram();
    for(unsigned s = 0; s < shaders.size(); s++) glAttachShader(progID, shaders[s].shaderID);
    glLinkProgram(progID);
    GLint logState;
    glGetProgramiv(progID, GL_LINK_STATUS, &logState);
    if (!logState) {
        GLchar infoLog[512];
        glGetProgramInfoLog(progID, 512, NULL, infoLog);
        puts(infoLog);
        logError(__FILE__, __LINE__, error_linkage);
    } else puts("Shader program linked successfuly");
}