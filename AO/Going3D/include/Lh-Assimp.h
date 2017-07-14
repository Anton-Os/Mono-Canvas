#include "Common.h"

#include <vector>

#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <assimp/postprocess.h>

bool Import3DFromFile( const std::string& pFile);
int LoadGLTextures(const aiScene* scene);
void genVAOsAndUniformBuffer(const aiScene *sc);
void recursive_render (const aiScene *sc, const aiNode* nd);