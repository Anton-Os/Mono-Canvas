#include "graphics/GL4_Program.hpp"

static char error_shadersEmpty[] = "No shaders are attributed to this program";
static char error_shadersLots[] = "You cannot hold over 8 shaders in a single program";
static char error_stageDuplicates[] = "Duplicates of shader stages detected!";
static char error_incompleteVF[] = "Incomplete pipeline, vertex and fragment shader necissary";
static char error_linkage[] = "Shader program failed to link";
static char error_immutable[] = "Shader program is immutable";

static void detect_duplicates(std::bitset<6>* stage_bits_arg, std::vector<GL4_Shader>* shaders_arg){
    for(unsigned shaderElem = 0; shaderElem < shaders_arg->size(); shaderElem++){
        if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::vert){
            if(!stage_bits_arg->test(_GL4_Shader_Stage::vert)) stage_bits_arg->set(_GL4_Shader_Stage::vert);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        } else if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::frag){
            if(!stage_bits_arg->test(_GL4_Shader_Stage::frag)) stage_bits_arg->set(_GL4_Shader_Stage::frag);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        } else if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::tesc){
            if(!stage_bits_arg->test(_GL4_Shader_Stage::tesc)) stage_bits_arg->set(_GL4_Shader_Stage::tesc);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        } else if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::tese){
            if(!stage_bits_arg->test(_GL4_Shader_Stage::tese)) stage_bits_arg->set(_GL4_Shader_Stage::tese);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        } else if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::geom){
            if(!stage_bits_arg->test(_GL4_Shader_Stage::geom)) stage_bits_arg->set(_GL4_Shader_Stage::geom);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        } else if(shaders_arg->at(shaderElem).stage == _GL4_Shader_Stage::comp){
            if(!stage_bits_arg->test(_GL4_Shader_Stage::comp)) stage_bits_arg->set(_GL4_Shader_Stage::comp);
            else logError(__FILE__, __LINE__, error_stageDuplicates);
        }
    }
}

void GL4_Program::add_shader(GL4_Shader* shader_arg) {
    if(immutable) logError(__FILE__, __LINE__, error_immutable);
    if(mShaders.size() > 8) logError(__FILE__, __LINE__, error_shadersLots);
    mShaders.push_back(*shader_arg);
    return;
}

void GL4_Program::create(){
    if(immutable) logError(__FILE__, __LINE__, error_immutable);
    if(mShaders.empty()) logError(__FILE__, __LINE__, error_shadersEmpty);
    detect_duplicates(&mStage_bits, &mShaders);
    if(!mStage_bits.test(_GL4_Shader_Stage::vert) || !mStage_bits.test(_GL4_Shader_Stage::frag)) logError(__FILE__, __LINE__, error_incompleteVF);

    mProgID = glCreateProgram();
    for(unsigned s = 0; s < mShaders.size(); s++) glAttachShader(mProgID, mShaders[s].shaderID);
    glLinkProgram(mProgID);
    GLint logState;
    glGetProgramiv(mProgID, GL_LINK_STATUS, &logState);
    if (!logState) {
        GLchar infoLog[512];
        glGetProgramInfoLog(mProgID, 512, NULL, infoLog);
        puts(infoLog);
        logError(__FILE__, __LINE__, error_linkage);
    } else puts("Shader program linked successfuly");

    immutable = true;
}