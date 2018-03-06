#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_LOAD_SHADERS_H
    #include "graphics/GL4_LoadShaders.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "graphics/GL4_Vertex.hpp"
#endif

#ifndef GL4_SHADER_H
    class GL4_Shader {
    public:
        GL4_Shader(const std::string& filePath_arg){
            mFilePath = filePath_arg;
            mShaderID = compileShader(mFilePath, &mStage);
        }
        std::vector<GL4_Shader_Vertex_Format> mInputs;
        std::vector<GL4_Shader_Vertex_Format> mOutputs;
        const GLuint *const get_shaderID() const { return &mShaderID; }
        _GL4_Shader_Stage::Pick get_stage() const { return mStage; }
    protected:
        GLuint mShaderID;
        _GL4_Shader_Stage::Pick mStage;
        std::string mFilePath;
    };
#define GL4_SHADER_H
#endif