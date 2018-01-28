#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

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
        GLushort version = 440;
        GL4_Shader(GL4_Shader_Stage::Pick pick){ stage = pick; }
        // std::string name = "Shader";
        void add_input(GL4_Vertex_Format* vertex);
        void add_input(GL4_Vertex_Format* vertex, unsigned location);
        void add_output(GL4_Vertex_Format* vertex);
        void add_output(GL4_Vertex_Format* vertex, unsigned location);
        // void add_uniform(GL4_Uniform* uniform)
        void create(const std::string& fileName);
        GL4_Shader_Stage::Pick get_stage(){ return stage; }
        GLboolean get_ready(){ return ready; }
    private:
        void compose_vertex_shader(std::string& shader_source);
        GLboolean ready = false;
        GL4_Shader_Stage::Pick stage;
        std::vector<GL4_Vertex_Format*> inputs;
        std::vector<GL4_Vertex_Format*> outputs;
    };

    static std::string write_input_entry(GLint location, const std::string& name, const std::string& type);
    static std::string write_output_entry(GLint location, const std::string& name, const std::string& type);
#define GL4_SHADER_H
#endif