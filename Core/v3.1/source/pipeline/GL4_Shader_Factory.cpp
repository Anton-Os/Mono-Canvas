#include "GL4/GL4_Shader_Factory.hpp"

static GL4_Shader gen_Idle_vert(const std::string& parentDir, GL4_Vertex_Factory* factory){
    GL4_Shader shader(parentDir + "//shaders//Idle.vert", _GL4_Shader_Stage::vert);
    GL4_Vertex_Format_Alt pos_3f(factory->get_shader_format(_GL4_Vertex_Feed::pos_3f));
    shader.inputs.push_back(pos_3f);
    GL4_Vertex_Format_Alt color_4f(factory->get_shader_format(_GL4_Vertex_Feed::color_4f));
    shader.inputs.push_back(color_4f);
    shader.outputs.push_back(color_4f);
}

static GL4_Program gen_Idle_program(_GL4_Program_ID::Pick progID, const std::string& parentDir, GL4_Vertex_Factory* factory){
    GL4_Vertex_Format_Alt pos_3f(factory->get_shader_format(_GL4_Vertex_Feed::pos_3f));
    GL4_Vertex_Format_Alt color_4f(factory->get_shader_format(_GL4_Vertex_Feed::color_4f));

    GL4_Shader vertex_shader(parentDir + "//shaders//Idle.vert", _GL4_Shader_Stage::vert);
    vertex_shader.inputs.push_back(pos_3f);
    vertex_shader.inputs.push_back(color_4f);
    vertex_shader.outputs.push_back(color_4f);

    GL4_Shader fragment_shader(parentDir + "//shaders//Idle.frag", _GL4_Shader_Stage::frag);
    fragment_shader.inputs.push_back(color_4f);
    fragment_shader.outputs.push_back(color_4f);

    GL4_Program program(progID);
    program.add_shader(&vertex_shader);
    program.add_shader(&fragment_shader);
    program.create();
    return program;
}

void GL4_Shader_Factory::create() {
    programs.resize(SHADER_FACTORY_PROG_COUNT);
    programs[_GL4_Program_ID::Idle] = gen_Idle_program(_GL4_Program_ID::Idle, parentDir, vertexFactory);
}