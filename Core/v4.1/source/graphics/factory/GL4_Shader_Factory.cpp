#include "graphics/factory/GL4_Shader_Factory.hpp"

static char error_programSupport[] = "Program not supported";
static char error_dynamicMode[] = "Cannot invoke create(), shader factory is dynamic";

/* static GL4_Shader gen_Idle_vert_shader(std::string parentDir, GL4_Vertex_Factory* vertexFactory_arg){
    GL4_Shader shader(parentDir + "//shaders//Idle.vert");

    shader.add_input(GL4_Shader_Vertex_Format(vertexFactory_arg->get_format(_GL4_Vertex_Feed_ID::pos_3f)));
    shader.add_input(GL4_Shader_Vertex_Format(vertexFactory_arg->get_format(_GL4_Vertex_Feed_ID::color_4f)));
} */

static GL4_Program gen_Idle_program(std::string parentDir, GL4_Vertex_Factory * vertexFactory_arg){
    GL4_Program program;

    GL4_Shader vertexShader(parentDir + "//shaders//Idle.vert");
    vertexShader.mInputs.push_back(GL4_Shader_Vertex_Format(vertexFactory_arg->get_format(_GL4_Vertex_Feed_ID::pos_3f)));
    vertexShader.mInputs.push_back(GL4_Shader_Vertex_Format(vertexFactory_arg->get_format(_GL4_Vertex_Feed_ID::color_4f)));
    vertexShader.mOutputs.push_back(GL4_Shader_Vertex_Format(vertexFactory_arg->get_format(_GL4_Vertex_Feed_ID::color_4f)));
    program.attach_shader(&vertexShader);

    GL4_Shader fragmentShader(parentDir + "//shaders//Idle.frag");
    fragmentShader.mInputs.push_back(GL4_Shader_Vertex_Format(vertexFactory_arg->get_format(_GL4_Vertex_Feed_ID::color_4f)));
    fragmentShader.mOutputs.push_back(GL4_Shader_Vertex_Format(vertexFactory_arg->get_format(_GL4_Vertex_Feed_ID::frag_4f)));
    program.attach_shader(&fragmentShader);

    return program;
}

static GLuint appendFormat(_GL4_Program_ID::Pick progID_arg, std::string parentDir_arg, GL4_Vertex_Factory * vertexFactory_arg, std::vector<GL4_Program>* programs_arg){
    switch(progID_arg){
        case _GL4_Program_ID::Idle:
            programs_arg->push_back(gen_Idle_program(parentDir_arg, vertexFactory_arg));
            break;
        default:
            logError(__FILE__, __LINE__, error_programSupport);
            break;
    }
    return programs_arg->size() - 1;
}

GL4_Program GL4_Shader_Factory::get_program(_GL4_Program_ID::Pick progID_arg){
    GL4_Program program;
    if(mStaticMode) program = mPrograms[progID_arg];
    else {
        if(! mProgramBits.test(progID_arg)){
            mProgramIndices[progID_arg] = appendFormat(progID_arg, mParentDir, mVertexFactory, &mPrograms);
            mProgramBits.set(progID_arg);
        }
        program = mPrograms[mProgramIndices[progID_arg]];
    }
    program.create();
    return program;
}

void GL4_Shader_Factory::create(){
    if(mPrograms.empty()) logError(__FILE__, __LINE__, error_dynamicMode);
    mPrograms.resize(SHADER_FACTORY_ENTRY_COUNT);
    mPrograms[_GL4_Program_ID::Idle] = gen_Idle_program(mParentDir, mVertexFactory);
    mProgramBits.set();
    mStaticMode = true;
}