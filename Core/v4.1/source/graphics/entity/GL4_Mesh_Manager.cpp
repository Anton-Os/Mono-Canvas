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

GL4_Mesh* GL4_Mesh_Manager::add_mesh(GLuint vertexCount_arg, std::initializer_list<const GL4_Vertex_Format*> formats_arg){
	std::vector<GL4_Vertex_Feed> feeds;
	for(unsigned list_elem = 0; list_elem < formats_arg.size(); list_elem++){
		// feeds.push_back(GL4_Vertex_Feed(mVBOs[mVBO_used], const_cast<GL4_Vertex_Format*>(std::begin(formats_arg))));
		feeds.push_back(GL4_Vertex_Feed(&mVBOs[mVBO_used], *(formats_arg.begin() + list_elem)));
		//feeds.push_back(GL4_Vertex_Feed(mVBOs[mVBO_used], const_cast<const GL4_Vertex_Format*>(std::begin(formats_arg))));
		mVBO_used++;
		if(mVBO_used > mVBO_count) logError(__FILE__, __LINE__, error_vboShort);
	}
	//mMeshes.push_back(GL4_Mesh(&mVAOs[mVAO_used], &mVBOs[mVBO_used], vertexCount_arg, { GL4_Vertex_Feed(&mVBOs[mVBO_used] ...) }));
    mMeshes.push_back(GL4_Mesh(&mVAOs[mVAO_used], &mVBOs[mVBO_used], vertexCount_arg, &feeds));
	mVAO_used++;
	if(mVAO_used > mVAO_count) logError(__FILE__, __LINE__, error_vaoShort);
	mVBO_used++;
	if(mVBO_used > mVBO_count) logError(__FILE__, __LINE__, error_vboShort);
	return &mMeshes[mMeshes.size() - 1];
}
