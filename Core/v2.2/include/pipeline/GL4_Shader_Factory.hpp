#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "geometry/GL4_Vertex.hpp"
#endif

#ifndef GL4_VERTEX_FACTORY_H
    #include "geometry/GL4_Vertex_Factory.hpp"
#endif

#ifndef GL4_SHADER_H
    #include "pipeline/GL4_Shader.hpp"
#endif

#ifndef GL4_PROGRAM_H
    #include "pipeline/GL4_Program.hpp"
#endif

#define SHADER_FACTORY_PROG_COUNT 1

#ifndef GL4_SHADER_FACTORY_H
    namespace _GL4_Program_ID {
        typedef enum { idle } Pick;
    }

    class GL4_Shader_Factory {
        GL4_Shader_Factory(const std::string& parentDir_arg, GL4_Vertex_Factory* factory_arg){ 
            create(parentDir_arg, factory_arg); 
        }
        ~GL4_Shader_Factory(){ delete[] programs; }
    private:
        GL4_Program* programs = new GL4_Program[SHADER_FACTORY_PROG_COUNT];
        void create(const std::string& parentDir_arg, GL4_Vertex_Factory* factory_arg);
    };
#define GL4_SHADER_FACTORY_H
#endif