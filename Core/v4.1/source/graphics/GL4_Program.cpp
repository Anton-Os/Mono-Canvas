#include "graphics/GL4_Program.hpp"

static char error_afterCreate[] = "Cannot perform after create() invoked";
static char error_reusedStage[] = "Shader stage has been reused";
static char error_incompleteVF[] = "Incomplete pipeline, vertex and fragment shader absemt";
static char error_shadersEmpty[] = "No shaders are attributed to this program";
static char error_linkage[] = "Shader program failed to link";

void GL4_Program::attach_shader(const GL4_Shader* shader_arg){
    if(mReady) logError(__FILE__, __LINE__, error_afterCreate);
    if(mStageBits.test(shader_arg->get_stage())) logError(__FILE__, __LINE__, error_reusedStage);

    mShaders.push_back(*shader_arg);
    mStageBits.set(shader_arg->get_stage());
    mShaderIndices[shader_arg->get_stage()] = mShaders.size() - 1;
}

void GL4_Program::create(){
    if(mReady) logError(__FILE__, __LINE__, error_afterCreate);
    if(mShaders.empty()) logError(__FILE__, __LINE__, error_shadersEmpty);
    if(!mStageBits.test(_GL4_Shader_Stage::vert) || !mStageBits.test(_GL4_Shader_Stage::frag)) logError(__FILE__, __LINE__, error_incompleteVF);

    mProgID = glCreateProgram();
    for(unsigned s = 0; s < mShaders.size(); s++) glAttachShader(mProgID, *(mShaders[s].get_shaderID()));
    glLinkProgram(mProgID);
    GLint logState;
    glGetProgramiv(mProgID, GL_LINK_STATUS, &logState);
    if (!logState) {
        GLchar infoLog[512];
        glGetProgramInfoLog(mProgID, 512, NULL, infoLog);
        puts(infoLog);
        logError(__FILE__, __LINE__, error_linkage);
    } else puts("Shader program linked successfuly");

    mReady = true;
}