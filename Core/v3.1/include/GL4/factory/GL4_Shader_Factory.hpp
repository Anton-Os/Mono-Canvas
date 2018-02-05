#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "GL4/GL4_Vertex.hpp"
#endif

#ifndef GL4_VERTEX_FACTORY_H
    #include "GL4/factory/GL4_Vertex_Factory.hpp"
#endif

#ifndef GL4_SHADER_H
    #include "GL4/GL4_Shader.hpp"
#endif

#ifndef GL4_PROGRAM_H
    #include "GL4/GL4_Program.hpp"
#endif

#define SHADER_FACTORY_PROG_COUNT 1

#ifndef GL4_SHADER_FACTORY_H
    class GL4_Shader_Factory {
    public:
        GL4_Shader_Factory(const std::string& parentDir_arg, GL4_Vertex_Factory* factory_arg){ 
            parentDir = parentDir_arg;
            vertexFactory = factory_arg;
        }
        GL4_Program get_program(_GL4_Program_ID::Pick progID_arg);
        void create();
    private:
        std::string parentDir;
        GL4_Vertex_Factory* vertexFactory;
        std::vector<GL4_Program> programs;
        std::bitset<SHADER_FACTORY_PROG_COUNT> program_bits;
        void append_program(GL4_Program* program_arg);
    };
#define GL4_SHADER_FACTORY_H
#endif