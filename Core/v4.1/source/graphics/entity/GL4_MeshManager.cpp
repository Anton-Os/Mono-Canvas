#include "graphics/entity/GL4_MeshManager.hpp"

GL4_MeshManager::GL4_MeshManager() {
    glGenVertexArrays(MMANAGER_VERTEX_ARRAY_COUNT, &mVertexArrays[0]);
    glGenBuffers(MMANAGER_VERTEX_BUFFER_COUNT, &mBuffers[0]);
}

void GL4_MeshManager::createMesh(GLuint vertexCount_arg){
    mMeshes.push_back(GL4_Mesh(vertexCount_arg, mVertexArrays[mUsedVertexArray_count]));
    mUsedVertexArray_count++;
}