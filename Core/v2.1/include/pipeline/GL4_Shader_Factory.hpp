#include <string>
#include <vector>

#include <GL/glew.h>

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

#ifndef GL4_SHADER_FACTORY_H

    static bool match_stage(GL4_Shader_Stage::Pick stage, std::vector<GL4_Shader>* shadersArg);

    class GL4_Shader_Factory {
    public:
        void add_shader(GL4_Shader* shader);
    private:
        std::vector<GL4_Shader> shaders;
    };

#define GL4_SHADER_FACTORY_H
#endif