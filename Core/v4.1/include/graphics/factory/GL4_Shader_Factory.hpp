#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_FACTORY_H
    #include "graphics/factory/GL4_Vertex_Factory.hpp"
#endif

#ifndef GL4_SHADER_H
    #include "graphics/GL4_Shader.hpp"
#endif

#ifndef GL4_PROGRAM_H
    #include "graphics/GL4_Program.hpp"
#endif

#define SHADER_FACTORY_ENTRY_COUNT 6

namespace _GL4_Shader_ID {
    typedef enum { Idle_vert, Idle_frag, Tones_vert, Tones_frag, Flatland_vert, Flatland_frag } Pick;
}

#ifndef GL4_SHADER_FACTORY_H
    class GL4_Shader_Factory {
    public:
        void create();
        GL4_Program get_program(_GL4_Program_ID::Pick programID_arg);
    private:
        GLboolean mStaticMode = false;
        std::vector<GL4_Shader> mShaders;
        std::bitset<SHADER_FACTORY_ENTRY_COUNT> mShaderBits;
        GLuint mShaderIndices[SHADER_FACTORY_ENTRY_COUNT];
        GL4_Vertex_Factory mVertexFactory;
    };
#define GL4_SHADER_FACTORY_H
#endif