#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_REGISTRY_H
    #include "graphics/factory/GL4_Vertex_Registry.hpp"
#endif

#ifndef GL4_SHADER_H
    #include "graphics/GL4_Shader.hpp"
#endif

#ifndef GL4_PROGRAM_H
    #include "graphics/GL4_Program.hpp"
#endif

#define SHADER_FACTORY_ENTRY_COUNT 6

#ifndef GL4_SHADER_FACTORY_H
    class GL4_Shader_Factory {
    public:
        GL4_Shader_Factory(const std::string& parentDir_arg){
            mParentDir = parentDir_arg;
        }
        ~GL4_Shader_Factory(){
            delete mVertexRegistry;
            mVertexRegistry = nullptr;
        }
        void create();
        GL4_Program get_program(_GL4_Program_ID::Pick programID_arg);
    private:
        std::string mParentDir;
        GLboolean mStaticMode = false;
        std::vector<GL4_Program> mPrograms;
        std::bitset<SHADER_FACTORY_ENTRY_COUNT> mProgramBits;
        GLuint mProgramIndices[SHADER_FACTORY_ENTRY_COUNT];
        GL4_Vertex_Registry* mVertexRegistry = new GL4_Vertex_Registry;
    };
#define GL4_SHADER_FACTORY_H
#endif