#define PIPELINE_X
#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "graphics/GL4_Vertex.hpp"
#endif

#define VERTEX_REGISTRY_ENTRY_COUNT 6

#ifndef GL4_VERTEX_REGISTRY_H
    class GL4_Vertex_Registry {
    public:
        void create();
        GL4_Vertex_Format* get_format(_GL4_Vertex_Feed_ID::Pick vertexID_arg);
    private:
        GLboolean mStaticMode = false;
        std::vector<GL4_Vertex_Format> mFormats;
        std::bitset<VERTEX_REGISTRY_ENTRY_COUNT> mFormatBits;
        GLuint mFormatIndices[VERTEX_REGISTRY_ENTRY_COUNT];
    };
#define GL4_VERTEX_REGISTRY_H
#endif