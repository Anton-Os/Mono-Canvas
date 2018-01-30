#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_SHADER_H
    #include "pipeline/GL4_Shader.hpp"
#endif

#ifndef GL4_PROGRAM_H
    class GL4_Program {
        void add_shader(GL4_Shader* shader, const std::string& path);
    private:
        GLuint id;
        std::vector<GL4_Shader> shaders;
    };
#define GL4_PROGRAM_H
#endif