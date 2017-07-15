#include "Common.h"
#include "Assimp.h"

int assimpImportCPP( const std::string& pFile) {

  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile( pFile, 
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType
  );

  if(!scene) {
    std::cout << "File import has failed due to error: " << GetErrorString() << std::endl;
    return -1;
  } else {
    std::cout << "File has been successfully imported from" << pFile << std::endl;
  }

  if(scene->HasMeshes){
    // Extract the properties of the meshes and convert to custom C++ struct
  } else {
    std::cout << "Scene does not contain meshes" << std::endl;
    return -2;
  }
  

  if(scene->HasTextures()){
    // Extract the textures, convert them to KTX if nessicary, and execute image loading funcion
  } else {
    std::cout << "Scene does not contain textures" << std::endl;
    return -2;
  }
  
  
  return 0;
}