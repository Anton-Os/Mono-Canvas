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

void GL4_Shader_Factory::create(const std::string& parentDir, GL4_Vertex_Factory* factory) {
    GL4_Vertex_Format_Alt pos_3f(factory->get_format(_GL4_Vertex_Feed::pos_3f));
    GL4_Vertex_Format_Alt color_4f(factory->get_format(_GL4_Vertex_Feed::color_4f));
}