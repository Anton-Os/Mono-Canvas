#include "graphics/factory/GL4_Shader_Factory.hpp"

static char error_findFormat[] = "Requested format could not be obtained";

static GLint match_vAttrib(_GL4_Program_ID::Pick pick_arg, std::vector<GL4_Program>* programs_arg){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < programs_arg->size(); v++){
        if(pick_arg == programs_arg->at(v).mID){
            savedAttrib = v;
            break;
        }
    }
    return savedAttrib;
}

static GL4_Program gen_Idle_program(const std::string& parentDir_arg, GL4_Vertex_Factory* vertex_factory_arg){
    GL4_Shader_Vertex_Format pos_3f(vertex_factory_arg->get_shader_format(_GL4_Vertex_Feed_ID::pos_3f));
    GL4_Shader_Vertex_Format color_4f(vertex_factory_arg->get_shader_format(_GL4_Vertex_Feed_ID::color_4f));
    GL4_Shader_Vertex_Format frag_4f(vertex_factory_arg->get_shader_format(_GL4_Vertex_Feed_ID::frag_4f));

    GL4_Shader vertex_shader(parentDir_arg + "//shaders//Idle.vert", _GL4_Shader_Stage::vert);
    vertex_shader.inputs.push_back(pos_3f);
    vertex_shader.inputs.push_back(color_4f);
    vertex_shader.outputs.push_back(color_4f);

    GL4_Shader fragment_shader(parentDir_arg + "//shaders//Idle.frag", _GL4_Shader_Stage::frag);
    fragment_shader.inputs.push_back(color_4f);
    fragment_shader.outputs.push_back(frag_4f);

    GL4_Program program(_GL4_Program_ID::Idle);
    program.add_shader(&vertex_shader);
    program.add_shader(&fragment_shader);
    program.create();
    return program;
}

static GL4_Program gen_Tones_program(const std::string& parentDir_arg, GL4_Vertex_Factory* vertex_factory_arg, GL4_Uniform_Factory* uniform_factory_arg){
    GL4_Shader_Vertex_Format pos_3f(vertex_factory_arg->get_shader_format(_GL4_Vertex_Feed_ID::pos_3f));
    // GL4_Shader_Vertex_Format color_4f(vertex_factory_arg->get_shader_format(_GL4_Vertex_Feed_ID::color_4f));
    GL4_Shader_Vertex_Format frag_4f(vertex_factory_arg->get_shader_format(_GL4_Vertex_Feed_ID::frag_4f));

    GL4_Shader vertex_shader(parentDir_arg + "//shaders//Tones.vert", _GL4_Shader_Stage::vert);
    vertex_shader.inputs.push_back(pos_3f);

    GL4_Shader fragment_shader(parentDir_arg + "//shaders//Tones.frag", _GL4_Shader_Stage::frag);
    fragment_shader.outputs.push_back(frag_4f);

    GL4_Program program(_GL4_Program_ID::Tones);
    
    program.add_shader(&vertex_shader);
    program.add_shader(&fragment_shader);
    program.create();

    GL4_Uniform_Basic uniform_renderMode(program.get_progID_ptr(), uniform_factory_arg->get_uniform_b(_GL4_Uniform_Basic_ID::renderMode));
    program.add_uniform(&uniform_renderMode);

    return program;
}

static GL4_Program gen_Flatland_program(const std::string& parentDir_arg, GL4_Vertex_Factory* vertex_factory_arg, GL4_Uniform_Factory* uniform_factory_arg){
    // GL4_Shader_Vertex_Format pos_3f(vertex_factory_arg->get_shader_format(_GL4_Vertex_Feed_ID::pos_3f));
    GL4_Shader_Vertex_Format pos_2f(vertex_factory_arg->get_shader_format(_GL4_Vertex_Feed_ID::pos_2f));
    GL4_Shader_Vertex_Format frag_4f(vertex_factory_arg->get_shader_format(_GL4_Vertex_Feed_ID::frag_4f));

    GL4_Shader vertex_shader(parentDir_arg + "//shaders//Flatland.vert", _GL4_Shader_Stage::vert);
    vertex_shader.inputs.push_back(pos_2f);

    GL4_Shader fragment_shader(parentDir_arg + "//shaders//Flatland.frag", _GL4_Shader_Stage::frag);
    fragment_shader.outputs.push_back(frag_4f);

    GL4_Program program(_GL4_Program_ID::Flatland);
    
    program.add_shader(&vertex_shader);
    program.add_shader(&fragment_shader);
    program.create();

    GL4_Uniform_Basic uniform_renderMode(program.get_progID_ptr(), uniform_factory_arg->get_uniform_b(_GL4_Uniform_Basic_ID::renderMode));
    program.add_uniform(&uniform_renderMode);

    return program;
}


void GL4_Shader_Factory::create() {
    mPrograms.resize(SHADER_FACTORY_PROG_COUNT);
    mPrograms[_GL4_Program_ID::Idle] = gen_Idle_program(mParentDir, mVertexFactory);
    mPrograms[_GL4_Program_ID::Tones] = gen_Tones_program(mParentDir, mVertexFactory, mUniformFactory);
    mPrograms[_GL4_Program_ID::Flatland] = gen_Flatland_program(mParentDir, mVertexFactory, mUniformFactory);
    mProgram_bits.set();
}

void GL4_Shader_Factory::append_program(_GL4_Program_ID::Pick program_arg){
    switch(program_arg){
        case _GL4_Program_ID::Idle :
            mPrograms.push_back(gen_Idle_program(mParentDir, mVertexFactory));
            break;
        case _GL4_Program_ID::Tones :
            mPrograms.push_back(gen_Tones_program(mParentDir, mVertexFactory, mUniformFactory));
            break;
        case _GL4_Program_ID::Flatland :
            mPrograms.push_back(gen_Flatland_program(mParentDir, mVertexFactory, mUniformFactory));
            break;
    }
    mProgram_bits.set(program_arg);
}

GL4_Program GL4_Shader_Factory::get_program(_GL4_Program_ID::Pick pick_arg){
    /* if(mProgram_bits.all())
        return mPrograms[pick_arg]; */
    if(!mProgram_bits.test(pick_arg))
        append_program(pick_arg);

    GLint savedAttrib = match_vAttrib(pick_arg, &mPrograms);

    if(savedAttrib < 0) logError(__FILE__, __LINE__, error_findFormat);
    else return mPrograms[savedAttrib];
}
