#include "Loaders.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void assimpImport(std::string filepath, GL4_Tree* tree){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath.c_str(),
            aiProcess_CalcTangentSpace       | 
            aiProcess_Triangulate            |
            aiProcess_JoinIdenticalVertices  |
            aiProcess_SortByPType |
            aiProcess_GenNormals |
            aiProcess_PreTransformVertices
    );
}
