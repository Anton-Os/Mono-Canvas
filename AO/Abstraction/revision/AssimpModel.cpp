#include "Common.h"
#include "Abstraction.h"
#include <stack>
// #include "Assimp.h"

int iterateNodes(const aiScene* scene, std::vector<AssimpComposite>* MPerComponent){
  aiMesh** modelMeshes = scene->mMeshes;
  aiNode* rootNode = scene->mRootNode;
  std::stack<aiNode*> nodeStack;
  nodeStack.push(rootNode);
  while(! nodeStack.empty()){
    aiNode* currentNode = nodeStack.top();
    nodeStack.pop();
    aiNode** lastChild = currentNode->mChildren + currentNode->mNumChildren;

    for(aiNode** currentChild = currentNode->mChildren; currentChild != lastChild; ++currentChild){
      nodeStack.push(*currentChild);
    }

    unsigned int* nodeMeshes = currentNode->mMeshes;
    unsigned int nodeMeshCount = currentNode->mNumMeshes;
    aiMatrix4x4 relTransform = currentNode->mTransformation;
    
    for(aiNode* nextParent = currentNode->mParent; nullptr != nextParent; nextParent = nextParent->mParent)
    relTransform *= nextParent->mTransformation;

    AssimpComposite meshComponent;
    meshComponent.currentNode = currentNode;
    if(nodeMeshCount > 0){
      for(unsigned int m = 0; m < nodeMeshCount; m++){
        aiMesh* currentMesh = modelMeshes[nodeMeshes[m]];
        aiFace* lastFace = currentMesh->mFaces + currentMesh->mNumFaces;
        for(aiFace* currentFace = currentMesh->mFaces; currentFace != lastFace; ++currentFace)
          for(unsigned int i = 0; i < currentFace->mNumIndices; i++)
            meshComponent.faceIndex.push_back(currentFace->mIndices[i]);
        
        if(! currentMesh->HasPositions()) return -1;
        if( currentMesh->HasVertexColors(0)) meshComponent.renderParams[ImportCtrl::color] = true;
        else meshComponent.renderParams[ImportCtrl::color] = false;
        if( currentMesh->HasTextureCoords(0)) meshComponent.renderParams[ImportCtrl::texCoord] = true;
        else meshComponent.renderParams[ImportCtrl::texCoord] = false;
        if(! currentMesh->HasNormals()) return -2;

        for(unsigned int m = 0; m < currentMesh->mNumVertices; m++){
          MeshBlock currentBlock;
          currentBlock.pos = aiVector3D(currentMesh->mVertices[m]);
          if(meshComponent.renderParams[ImportCtrl::color]) 
            currentBlock.color = aiColor4D(currentMesh->mColors[0][m]);
          if(meshComponent.renderParams[ImportCtrl::texCoord]) 
            currentBlock.texCoord = aiVector3D(currentMesh->mTextureCoords[0][m]);
          currentBlock.normal = aiVector3D(currentMesh->mNormals[m]);
          meshComponent.modelMeshes.push_back(currentBlock);
        }
      } 
      meshComponent.renderParams[ImportCtrl::drawable] = true;
      std::cout << "renderParams are set to " << meshComponent.renderParams << std::endl;
    } else {
      meshComponent.renderParams[ImportCtrl::drawable] = false;
      std::cout << "renderParams are set to " << meshComponent.renderParams << std::endl;
    }
    meshComponent.relTransform = relTransform;
    MPerComponent->push_back(meshComponent);
  }
}

int assimpImportCPP(const std::string &pFile, std::vector<AssimpComposite>* MPerComponent){

  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType |
        aiProcess_GenNormals |
        aiProcess_PreTransformVertices
  );

  if(!scene) {
    std::cerr << "File import has failed due to error: " << importer.GetErrorString() << std::endl;
    return -1;
  } else std::cout << "File has been successfully imported from" << pFile << std::endl;

  if(! scene->HasMeshes()){
    std::cerr << "Scene does not contain meshes" << std::endl;
    return -2;
  } else iterateNodes(scene, MPerComponent);

  return 0;
}
