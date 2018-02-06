#include "graphics/factory/GL4_Shader_Factory.hpp"

static GL4_Program gen_Idle_program(_GL4_Program_ID::Pick progID, const std::string& parentDir_arg, GL4_Vertex_Factory* factory_arg){
    GL4_Shader_Vertex_Format pos_3f(factory_arg->get_shader_format(_GL4_Vertex_Feed::pos_3f));
    GL4_Shader_Vertex_Format color_4f(factory_arg->get_shader_format(_GL4_Vertex_Feed::color_4f));

    GL4_Shader vertex_shader(parentDir_arg + "//shaders//Idle.vert", _GL4_Shader_Stage::vert);
    vertex_shader.inputs.push_back(pos_3f);
    vertex_shader.inputs.push_back(color_4f);
    vertex_shader.outputs.push_back(color_4f);

    GL4_Shader fragment_shader(parentDir_arg + "//shaders//Idle.frag", _GL4_Shader_Stage::frag);
    fragment_shader.inputs.push_back(color_4f);
    fragment_shader.outputs.push_back(color_4f);

    GL4_Program program(progID);
    program.add_shader(&vertex_shader);
    program.add_shader(&fragment_shader);
    program.create();
    return program;
}

void GL4_Shader_Factory::create() {
    mPrograms.resize(SHADER_FACTORY_PROG_COUNT);
    mPrograms[_GL4_Program_ID::Idle] = gen_Idle_program(_GL4_Program_ID::Idle, mParentDir, mVertexFactory);
    mProgram_bits.set();
}