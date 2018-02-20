#include "graphics/GL4_Program.hpp"

static char error_shadersEmpty[] = "No shaders are attributed to this program";
static char error_shadersLots[] = "You cannot hold over 8 shaders in a single program";
static char error_stageDuplicates[] = "Duplicates of shader stages detected!";
static char error_incompleteVF[] = "Incomplete pipeline, vertex and fragment shader necissary";
static char error_linkage[] = "Shader program failed to link";
static char error_immutable[] = "Shader program is immutable";
static char error_findFormat[] = "Requested format could not be obtained";

static GLint match_vAttrib(_GL4_Uniform_Basic_ID::Pick pick_arg, std::vector<GL4_Uniform_Basic>* uniforms_arg){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < uniforms_arg->size(); v++){
        if(pick_arg == uniforms_arg->at(v).mFormat->mID){
            savedAttrib = v;
            break;
        }
    }
    return savedAttrib;
}

static GLint match_vAttrib(_GL4_Uniform_Matrix_ID::Pick pick_arg, std::vector<GL4_Uniform_Matrix>* uniforms_arg){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < uniforms_arg->size(); v++){
        if(pick_arg == uniforms_arg->at(v).mFormat->mID){
            savedAttrib = v;
            break;
        }
    }
    return savedAttrib;
}

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
    if(mImmutable) logError(__FILE__, __LINE__, error_immutable);
    if(mShaders.size() > 8) logError(__FILE__, __LINE__, error_shadersLots);
    mShaders.push_back(*shader_arg);
    return;
}

void GL4_Program::add_uniform(GL4_Uniform_Basic* basic_arg){
    // if(mImmutable) logError(__FILE__, __LINE__, error_immutable);
    mUniforms_b.push_back(*basic_arg);
    return;
}

void GL4_Program::set_data(_GL4_Uniform_Basic_ID::Pick id_arg, void* data_arg){
    GLint savedAttrib = match_vAttrib(id_arg, &mUniforms_b);

    if(savedAttrib < 0) logError(__FILE__, __LINE__, error_findFormat);
    mUniforms_b[savedAttrib].set(data_arg);
}

void GL4_Program::add_uniform(GL4_Uniform_Matrix* matrix_arg){
    // if(mImmutable) logError(__FILE__, __LINE__, error_immutable);
    mUniforms_m.push_back(*matrix_arg);
    return;
}

void GL4_Program::set_data(_GL4_Uniform_Matrix_ID::Pick id_arg, void* data_arg){
    GLint savedAttrib = match_vAttrib(id_arg, &mUniforms_m);

    if(savedAttrib < 0) logError(__FILE__, __LINE__, error_findFormat);
    mUniforms_m[savedAttrib].set(data_arg);
}

void GL4_Program::create(){
    if(mImmutable) logError(__FILE__, __LINE__, error_immutable);
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

    mImmutable = true;
}
