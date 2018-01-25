#include <string>
#include <vector>

#include <GL/glew.h>

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef FILE_IO_H
    #include "loaders/FileIO.hpp"
#endif    

#ifndef GL4_VERTEX_H
    #include "geometry/GL4_Vertex.hpp"
#endif

#ifndef GL4_VERTEX_FACTORY_H
    #include "geometry/GL4_Vertex_Factory.hpp"
#endif

#ifndef GL4_SHADER_H

    namespace GL4_Shader_Stage {
        typedef enum { vert, frag, tesc, tese, geom, comp } Pick;
    }

    class GL4_Shader {
    public:
        GL4_Shader(GL4_Shader_Stage::Pick pick){ stage = pick; }
        // std::string name = "Shader";
        void add_input(GL4_Vertex* vertex);
        void add_input(GL4_Vertex* vertex, unsigned location);
        void add_output(GL4_Vertex* vertex);
        void add_output(GL4_Vertex* vertex, unsigned location);
        // void add_uniform(GL4_Uniform* uniform)
        void create(const std::string& fileName);
        GL4_Shader_Stage::Pick get_stage(){ return stage; }
        GLboolean get_ready(){ return ready; }
    private:
        GLboolean ready = false;
        GL4_Shader_Stage::Pick stage;
        std::vector<GL4_Vertex> inputs;
        std::vector<GL4_Vertex> outputs;
    };

#define GL4_SHADER_H
#endif