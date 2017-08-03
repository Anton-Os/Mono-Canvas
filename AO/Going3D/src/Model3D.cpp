#include "Common.h"
#include <stack>
// #include "Assimp.h"

void iterateNodes(aiNode* rootNode){
  std::stack<aiNode*> nodeStack;
  nodeStack.push(rootNode);
  while(! nodeStack.empty()){
    aiNode* node = nodeStack.top();
    nodeStack.pop();
    aiNode** endIt = node->mChildren + node->mNumChildren;
    for(aiNode** it = node->mChildren; it != endIt; ++it){
      nodeStack.push(*it);
    }
  }
}

void iterateNodes(const aiScene* scene){
  aiMesh** modelMeshes = scene->mMeshes;
  aiNode* rootNode = scene->mRootNode;
  std::stack<aiNode*> nodeStack;
  nodeStack.push(rootNode);
  while(! nodeStack.empty()){
    aiNode* currentNode = nodeStack.top();
    nodeStack.pop();
    aiNode** endIt = currentNode->mChildren + currentNode->mNumChildren;
    for(aiNode** it = currentNode->mChildren; it != endIt; ++it){
      nodeStack.push(*it);
    }
    unsigned int nodeMeshCount = currentNode->mNumMeshes;
    unsigned int* nodeMeshes = currentNode->mMeshes;
    ModelComposite Model;
    for(unsigned int m = 0; m < nodeMeshCount; m++){
        aiMesh* currentMesh = modelMeshes[nodeMeshes[m]];
        for(unsigned int f = 0; f < currentMesh->mNumFaces; f++) std::cout << "Inside face " << f << std::endl;
        for(unsigned int v = 0; v < currentMesh->mNumVertices; v++) std::cout << "Inside vertex position " << v << std::endl;
    }
  }
}

GLuint loadModelData(ModelStatic* Model){
  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(GL_ARRAY_BUFFER, Model->modelMeshes.size() * sizeof(Point), &Model->modelMeshes[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, pos));
  glEnableVertexAttribArray(0);
  if(Model->renderParams[ShaderCtrlBit::color] == 0){
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, color));
    glEnableVertexAttribArray(1);  
  }
  if(Model->renderParams[ShaderCtrlBit::texCoord] == 0){
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, texCoord));
    glEnableVertexAttribArray(2);
  }
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, normal));
  glEnableVertexAttribArray(3);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, Model->modelIndices.size() * sizeof(GLuint), &Model->modelIndices[0], GL_STATIC_DRAW);

  GLenum errorLog = glGetError();
  return VAO;
}

GLuint loadModelData(ModelComposite* Model){
  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(GL_ARRAY_BUFFER, Model->modelMeshes.size() * sizeof(Point), &Model->modelMeshes[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, pos));
  glEnableVertexAttribArray(0);
  if(Model->renderParams[ShaderCtrlBit::color] == 0){
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, color));
    glEnableVertexAttribArray(1);  
  }
  if(Model->renderParams[ShaderCtrlBit::texCoord] == 0){
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, texCoord));
    glEnableVertexAttribArray(2);
  }
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, normal));
  glEnableVertexAttribArray(3);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, Model->modelIndices.size() * sizeof(GLuint), &Model->modelIndices[0], GL_STATIC_DRAW);

  GLenum errorLog = glGetError();
  return VAO;
}

int assimpImportCPP(const std::string &pFile, ModelStatic* Model){

  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(pFile,
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

  if(scene->HasMeshes()){
    std::vector<std::array<GLfloat, 3>> allVertexPos;
    std::vector<std::array<GLfloat, 4>> allVertexColors;
    std::vector<std::array<GLfloat, 2>> allVertexTexCoord;
    std::vector<std::array<GLfloat, 3>> allVertexNormals;

    aiNode* currentNode = scene->mRootNode;
    aiMesh** modelMeshes = scene->mMeshes;
    unsigned int meshesCount = scene->mNumMeshes;
    std::cout << "Number of meshes present in scene is " << meshesCount << std::endl;

    for(unsigned int i = 0; i < meshesCount; i++){
      unsigned int meshVertexCount = modelMeshes[i]->mNumVertices;
      unsigned int meshFaceCount = modelMeshes[i]->mNumFaces;
      aiFace* meshFaces = modelMeshes[i]->mFaces;

      if(modelMeshes[i]->HasFaces()){
        std::cout << "Mesh # " << i << " contains faces" << std::endl;
        for(unsigned int f = 0; f < meshFaceCount; f++){
          for(unsigned int i = 0; i < meshFaces[f].mNumIndices; i++){
            unsigned int currentIndex = meshFaces[f].mIndices[i];
            Model->modelIndices.push_back(currentIndex);
          }
        }
      } else {
        std::cerr << "Mesh # " << " does not contain faces" << std::endl;
        return -1;
      }

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
        Model->renderParams[ShaderCtrlBit::color] = 0;
      } else {
        std::cout << "Mesh # " << i << " does not contain vertex colors" << std::endl;
        if(Model->renderParams[ShaderCtrlBit::color] == 0){
          std::cout << "Proceeding to generate vertex colors..." << std::endl;
          srand(time(NULL));
          GLfloat randomColor_R, randomColor_G, randomColor_B;
          for(unsigned int c = 0; c < meshVertexCount; c++){
            if(c % 3 == 0){
              randomColor_R = static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX);
              randomColor_G = static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX);
              randomColor_B = static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX);
            }
            allVertexColors.push_back( { randomColor_R, randomColor_G, randomColor_B, 0.5f } );
          }
        } else {
          Model->renderParams[ShaderCtrlBit::color] = 1;
        }
      }

      if(modelMeshes[i]->HasTextureCoords(0)){
        std::cout << "Mesh # " << i << " contains texture coordinates" << std::endl;
        for(unsigned int tc = 0; tc < meshVertexCount; tc++){
            float tcX = modelMeshes[i]->mTextureCoords[0][tc].x;
            float tcY = modelMeshes[i]->mTextureCoords[0][tc].y;
            allVertexTexCoord.push_back( {tcX, tcY} );
        }
        Model->renderParams[ShaderCtrlBit::texCoord] = 0;
      } else {
        std::cout << "Mesh # " << i << " does not contain texture coordinates" << std::endl;
        for(unsigned int tc = 0; tc < meshVertexCount; tc++){
            allVertexTexCoord.push_back( {0.0, 0.0} );
        }
        Model->renderParams[ShaderCtrlBit::texCoord] = 1;
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

      Point currentMeshData;
      for(unsigned int md = 0; md < meshVertexCount; md++){
        currentMeshData.pos = allVertexPos.at(md);
        currentMeshData.color = allVertexColors.at(md);
        currentMeshData.texCoord = allVertexTexCoord.at(md);
        currentMeshData.normal = allVertexNormals.at(md);

        Model->modelMeshes.push_back(currentMeshData);
      }
    }
  } else {
      std::cout << "Scene does not contain meshes" << std::endl;
      return -1;
  }

  Model->VertexArray = loadModelData(Model);

  if(scene->HasMaterials()){
    // Extract Materials belonging to the scene
    unsigned int materialsCount = scene->mNumMaterials;
    std::cout << "Number of materials present in scene is " << materialsCount << std::endl;
    aiMaterial** modelMaterials = scene->mMaterials;
    for(unsigned int i = 0; i < materialsCount; i++){
      // Extracting through Individual Get()
      // Recursing through Material Properties
      GLuint materialPropertyCount = modelMaterials[i]->mNumProperties;
      aiMaterialProperty** materialProperties = modelMaterials[i]->mProperties;
      for(unsigned int p = 0; p < materialPropertyCount; p++){
        // Retrieve Material Property Data
        std::cout << "Inside Material # " << i << " Property # " << p << std::endl;
      }
    }

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

int assimpImportCPP(const std::string &pFile, std::vector<ModelComposite>* MPerComponent){

  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(pFile,
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

  if(scene->HasMeshes()){
    iterateNodes(scene);
  } else {
    std::cout << "Scene does not contain meshes" << std::endl;
    return -1;
  }

  /* for(int v = 0; v < MPerComponent.size(); v++) 
  MPerComponent.at(v)->VertexArray = loadModelData(MPerComponent.at(v));

  if(scene->HasMaterials()){
    // Extract Materials belonging to the scene
    unsigned int materialsCount = scene->mNumMaterials;
    std::cout << "Number of materials present in scene is " << materialsCount << std::endl;
    aiMaterial** modelMaterials = scene->mMaterials;
    for(unsigned int i = 0; i < materialsCount; i++){
      // Extracting through Individual Get()
      // Recursing through Material Properties
      GLuint materialPropertyCount = modelMaterials[i]->mNumProperties;
      aiMaterialProperty** materialProperties = modelMaterials[i]->mProperties;
      for(unsigned int p = 0; p < materialPropertyCount; p++){
        // Retrieve Material Property Data
        std::cout << "Inside Material # " << i << " Property # " << p << std::endl;
      }
    }

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
  */
  return 0;
}
