#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "graphics/GL4_Vertex.hpp"
#endif

#ifndef GL4_VERTEX_FACTORY_H
    #include "graphics/factory/GL4_Vertex_Factory.hpp"
#endif

#ifndef GL4_UNIFORM_H
    #include "graphics/GL4_Uniform.hpp"
#endif

#ifndef GL4_UNIFORM_FACTORY_H
    #include "graphics/factory/GL4_Uniform_Factory.hpp"
#endif

#ifndef GL4_SHADER_H
    #include "graphics/GL4_Shader.hpp"
#endif

#ifndef GL4_PROGRAM_H
    #include "graphics/GL4_Program.hpp"
#endif

#define SHADER_FACTORY_PROG_COUNT 3

#ifndef GL4_SHADER_FACTORY_H
    class GL4_Shader_Factory {
    public:
        GL4_Shader_Factory(const std::string& parentDir_arg, GL4_Vertex_Factory* vertex_factory_arg, GL4_Uniform_Factory* uniform_factory_arg){ 
            mParentDir = parentDir_arg;
            mVertexFactory = vertex_factory_arg;
            mUniformFactory = uniform_factory_arg;
        }
        GL4_Program get_program(_GL4_Program_ID::Pick progID_arg);
        void create();
    private:
        std::string mParentDir;
        GL4_Vertex_Factory* mVertexFactory;
        GL4_Uniform_Factory* mUniformFactory;
        std::vector<GL4_Program> mPrograms;
        std::bitset<SHADER_FACTORY_PROG_COUNT> mProgram_bits;
        void append_program(_GL4_Program_ID::Pick program_arg);
    };
#define GL4_SHADER_FACTORY_H
#endif