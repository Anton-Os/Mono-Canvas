#include "Common.h"
#include "Assimp.h"

int loadModelData(int* a){
  // myModel.data = 123;
  // a* = 123;
  std::cout << a << std::endl;
  return 0;
}

int assimpImportCPP(const std::string& pFile) {

  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile( pFile, 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType |
        aiProcess_GenNormals
  );

  if(!scene) {
    std::cout << "File import has failed due to error: " << importer.GetErrorString() << std::endl;
    return -1;
  } else {
    std::cout << "File has been successfully imported from" << pFile << std::endl;
  }

  std::vector<Point> allMeshes;

  /* aiNode* rootNode = scene->mRootNode;
  unsigned int childNodeCount = rootNode->mNumChildren;
  if(childNodeCount > 0){
    std::cout << "rootNode contains " << childNodeCount << " children" << std::endl;
  } else {
    std::cout << "rootNode has no children" << std::endl;
  } */

  if(scene->HasMeshes()){
    std::vector<std::array<GLfloat, 3>> allVertexPos;
    std::vector<std::array<GLfloat, 4>> allVertexColors;
    std::vector<std::array<GLfloat, 2>> allVertexTexCoord;
    std::vector<std::array<GLfloat, 3>> allVertexNormals;

    unsigned int meshesCount = scene->mNumMeshes;
    std::cout << "Number of meshes present in scene is " << meshesCount << std::endl;
    aiNode* currentNode = scene->mRootNode;
    aiMesh** modelMeshes = scene->mMeshes;

    for(unsigned int i = 0; i < meshesCount; i++){
      unsigned int meshVertexCount = modelMeshes[i]->mNumVertices;

      if(modelMeshes[i]->HasPositions()){
        std::cout << "Mesh # " << i << " contains vertex positions" << std::endl;
        for(unsigned int v = 0; v < meshVertexCount; v++){
          float vX = modelMeshes[i]->mVertices[v].x;
          float vY = modelMeshes[i]->mVertices[v].y;
          float vZ = modelMeshes[i]->mVertices[v].z;
          allVertexPos.push_back( {vX, vY, vZ} );
          // std::cout << vX << " " << vY << " " << vZ << std::endl;;
        }
      } else {
        std::cerr << "Mesh # " << i << " does not contain vertex positions" << std::endl;
        return -1;
      }

      if(modelMeshes[i]->HasVertexColors(0)){
        std::cout << "Mesh # " << i << " contains vertex colors" << std::endl;
        for(unsigned int c = 0; c < meshVertexCount; c++){
            float cR = modelMeshes[i]->mColors[0][c].r;
            float cG = modelMeshes[i]->mColors[0][c].g;
            float cB = modelMeshes[i]->mColors[0][c].b;
            float cA = modelMeshes[i]->mColors[0][c].a;
            allVertexColors.push_back( {cR, cG, cB, cA} );
        }
      } else {
        std::cerr << "Mesh # " << i << " does not contain vertex colors" << std::endl;
        for(unsigned int c = 0; c < meshVertexCount; c++){
            allVertexColors.push_back( {0.2588f, 0.5254f, 0.9568f, 1.0} ); // Soothing blue color
        }
      }

      if(modelMeshes[i]->HasTextureCoords(0)){
        std::cout << "Mesh # " << i << " contains texture coordinates" << std::endl;
        for(unsigned int tc = 0; tc < meshVertexCount; tc++){
            float tcX = modelMeshes[i]->mTextureCoords[0][tc].x;
            float tcY = modelMeshes[i]->mTextureCoords[0][tc].y;
            allVertexTexCoord.push_back( {tcX, tcY} );
        }
      } else {
        std::cerr << "Mesh # " << i << " does not contain texture coordinates" << std::endl;
        for(unsigned int tc = 0; tc < meshVertexCount; tc++){
            allVertexTexCoord.push_back( {0.0, 0.0} );
        }
      }

      if(modelMeshes[i]->HasNormals()){
        std::cout << "Mesh # " << i << " contains vertex normals" << std::endl;
        for(unsigned int n = 0; n < meshVertexCount; n++){
            float nX = modelMeshes[i]->mNormals[n].x;
            float nY = modelMeshes[i]->mNormals[n].y;
            float nZ = modelMeshes[i]->mNormals[n].z;
            allVertexNormals.push_back( {nX, nY, nZ} );
        }
      } else {
        std::cerr << "Mesh # " << i << " does not contain vertex normals" << std::endl;
        return -1;
      }
    }
  } else {
      std::cout << "Scene does not contain meshes" << std::endl;
      return -1;
  }

  if(scene->HasMaterials()){
    // Extract Materials belonging to the scene
    unsigned int materialsCount = scene->mNumMeshes;
    std::cout << "Number of materials present in scene is " << materialsCount << std::endl;
  } else {
    std::cout << "Scene does not contain materials" << std::endl;
    return -1;
  }

  if(scene->HasTextures()){
    // Extract the textures, convert them to KTX if nessicary, and execute image loading funcion
    unsigned int texturesCount = scene->mNumMeshes;
    std::cout << "Number of textures present in scene is " << texturesCount << std::endl;
  } else {
    std::cout << "Scene does not contain textures" << std::endl;
  }
  
  return 0;
}

