#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "geometry/GL4_Vertex.hpp"
#endif

#ifndef GL4_SHADER_H
    #include "pipeline/GL4_Shader.hpp"
#endif

#ifndef GL4_SHADER_FACTORY_H
    class GL4_Shader_Factory {
    public:
        void add_shader(GL4_Shader* shader);
    private:
        std::vector<GL4_Shader> shaders;
    };

    static bool match_stage(GL4_Shader_Stage::Pick stage, std::vector<GL4_Shader>* shadersArg);
#define GL4_SHADER_FACTORY_H
#endif