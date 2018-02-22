#include "graphics/factory/GL4_Shader_Factory.hpp"

static GL4_Shader gen_Idle_vert_shader(std::string parentDir, GL4_Vertex_Factory* vertexFactory_arg){
    GL4_Shader shader(parentDir + "//shaders//Idle.vert");

    shader.add_input(GL4_Shader_Vertex_Format(vertexFactory_arg->get_format(_GL4_Vertex_Feed_ID::pos_3f)));
    shader.add_input(GL4_Shader_Vertex_Format(vertexFactory_arg->get_format(_GL4_Vertex_Feed_ID::color_4f)));
}

void GL4_Shader_Factory::create(){

}