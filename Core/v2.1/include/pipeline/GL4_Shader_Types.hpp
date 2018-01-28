#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_SHADER_TYPES_H
    struct GL4_Shader_Type {
        /* GL4_Shader_Type(std::string& nameArg, std::string& typeArg){
            name = nameArg;
            type = typeArg;
        } */
        void create(const std::string& nameArg, const std::string& typeArg){
            name = nameArg;
            type = typeArg;
            // match_shaderType(type, &count, &size);
        }
        std::string name;
        std::string type;
        void* data = nullptr;
        unsigned count = 1; // Marked for change
        size_t size = sizeof(float); // Marked for change
    };

    static match_shaderType(const std::string& type, size_t* size, unsigned* count);
#define GL4_SHADER_TYPES_H
#endif