#include "graphics/entity/GL4_Mesh_Manager.hpp"

static char error_vaoShort[] = "Cannot encompass all VAOs";
static char error_vboShort[] = "Cannot encompass all Buffers";

GL4_Mesh_Manager::GL4_Mesh_Manager(GLuint VAO_count_arg, GLuint VBO_count_arg) {
	mVAO_count = VAO_count_arg;
    mVAOs.resize(mVAO_count);
    mVBO_count = VBO_count_arg;
    mVBOs.resize(mVBO_count);
    glGenVertexArrays(mVAO_count, mVAOs.data());
    glGenBuffers(mVBO_count, mVBOs.data());
}

GL4_Mesh* GL4_Mesh_Manager::add_mesh(GLuint vertexCount_arg){
	mMeshes.push_back(GL4_Mesh(&mVAOs[mVAO_used], &mVBOs[mVBO_used], vertexCount_arg));
	mVAO_used++;
	if(mVAO_used > mVAO_count) logError(__FILE__, __LINE__, error_vaoShort);
	mVBO_used++;
	if(mVBO_used > mVBO_count) logError(__FILE__, __LINE__, error_vboShort);
	return &mMeshes[mMeshes.size() - 1];
}