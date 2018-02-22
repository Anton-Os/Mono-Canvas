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
        void clear_inputs(){ mInputs.clear(); }
        void add_input(GL4_Shader_Vertex_Format shaderVertexFormat_arg){ mInputs.push_back(shaderVertexFormat_arg); }
        void clear_outputs(){ mOutputs.clear(); }
        void add_output(GL4_Shader_Vertex_Format shaderVertexFormat_arg){ mInputs.push_back(shaderVertexFormat_arg); }
        const GLuint *const mShaderID_ptr = &mShaderID;
        const _GL4_Shader_Stage::Pick *const mStage_ptr = &mStage;
    protected:
        GLuint mShaderID;
        _GL4_Shader_Stage::Pick mStage;
        std::string mFilePath;
        std::vector<GL4_Shader_Vertex_Format> mInputs;
        std::vector<GL4_Shader_Vertex_Format> mOutputs;
    };
#define GL4_SHADER_H
#endif