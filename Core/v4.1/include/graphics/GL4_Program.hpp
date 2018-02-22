#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_SHADER_H
    #include "graphics/GL4_Shader.hpp"
#endif

#ifndef GL4_PROGRAM_H
    class GL4_Program {
    public:
        /* ~GL4_Program(){
        } */
        void attach_shader(const GL4_Shader* shader_arg);
        void create();
    private:
        GLboolean mReady = false;
        GLuint mProgID;
        std::bitset<SHADER_STAGE_COUNT> mStageBits;
        std::vector<const GL4_Shader*> mShaders;
        GLuint mShaderIndices[SHADER_STAGE_COUNT];
    };
#define GL4_PROGRAM_H
#endif