#include "pipeline/GL4_Shader_Factory.hpp"

/* void GL4_Shader_Factory::create(const std::string& parentDir, GL4_Vertex_Factory* factory) {
    GL4_Shader idle_vert(parentDir + "//shaders//Idle.vert");
    idle_vert.inputs.resize(2);
    idle_vert.inputs[0] = factory->get_format(0);
    idle_vert.inputs[1] = factory->get_format(1);
    idle_vert.outputs.push_back(factory->get_format(1));
    GL4_Program idle;
    idle.add_shader(&idle_vert);
    return;
} */

static GL4_Shader gen_Idle_vert(const std::string& parentDir, GL4_Vertex_Factory* factory){
    GL4_Shader shader(parentDir + "//shaders//Idle.vert", _GL4_Shader_Stage::vert);
    GL4_Vertex_Format_Alt pos_3f(factory->get_shader_format(_GL4_Vertex_Feed::pos_3f));
    shader.inputs.push_back(pos_3f);
    GL4_Vertex_Format_Alt color_4f(factory->get_shader_format(_GL4_Vertex_Feed::color_4f));
    shader.inputs.push_back(color_4f);
    shader.outputs.push_back(color_4f);
}

static GL4_Shader gen_Idle_frag(const std::string& parentDir, GL4_Vertex_Factory* factory){
    GL4_Shader shader(parentDir + "//shaders//Idle.frag", _GL4_Shader_Stage::frag);
    GL4_Vertex_Format_Alt color_4f(factory->get_shader_format(_GL4_Vertex_Feed::color_4f));
    shader.inputs.push_back(color_4f);
    shader.outputs.push_back(color_4f);
}

static GL4_Program gen_Idle_program(_GL4_Program_ID::Pick progID, const std::string& parentDir, GL4_Vertex_Factory* factory){
    GL4_Program program(progID);
    GL4_Shader vert_shader = gen_Idle_vert(parentDir, factory);
    program.add_shader(&vert_shader);
    return program;
}

void GL4_Shader_Factory::create(const std::string& parentDir, GL4_Vertex_Factory* factory) {
    programs[_GL4_Program_ID::Idle] = gen_Idle_program(_GL4_Program_ID::Idle, parentDir, factory);
}