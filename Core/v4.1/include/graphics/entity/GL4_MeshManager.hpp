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

#ifndef GL4_MESH_H
    #include "graphics/entity/GL4_Mesh.hpp"
#endif

#define MMANAGER_VERTEX_ARRAY_COUNT 10
#define MMANAGER_VERTEX_BUFFER_COUNT 40

#ifndef GL4_MESH_MANAGER_H
    class GL4_MeshManager {
    public:
        GL4_MeshManager();
        void createMesh(GLuint vertexCount_arg);
        std::vector<GL4_Mesh> mMeshes;
    private:
        GLuint mVertexArrays[MMANAGER_VERTEX_ARRAY_COUNT];
        GLuint mUsedVertexArray_count = 0;
        GLuint mBuffers[MMANAGER_VERTEX_BUFFER_COUNT];
        GLuint mUsedBuffer_count = 0;
    };
#define GL4_MESH_MANAGER_H
#endif