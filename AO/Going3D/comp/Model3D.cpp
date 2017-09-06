#include "Common.h"
#include <stack>

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
  if(Model->renderParams[ShaderCtrlBit::color] == 1){
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, color));
    glEnableVertexAttribArray(1);  
  }
  if(Model->renderParams[ShaderCtrlBit::texCoord] == 1){
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, texCoord));
    glEnableVertexAttribArray(2);
  }
  if(Model->renderParams[ShaderCtrlBit::normal] == 1){
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, normal));
    glEnableVertexAttribArray(3);
  }

  if(Model->renderParams[ShaderCtrlBit::indexed] == 1){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Model->modelIndices.size() * sizeof(GLuint), &Model->modelIndices[0], GL_STATIC_DRAW);
  }
  GLenum errorLog = glGetError();
  return VAO;
}

GLuint loadModelData(ModelComposite* Model, std::bitset<5> renderParams){
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
  if(renderParams[ShaderCtrlBit::color] == 1){
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, color));
    glEnableVertexAttribArray(1);  
  }
  if(renderParams[ShaderCtrlBit::texCoord] == 1){
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, texCoord));
    glEnableVertexAttribArray(2);
  }
  if(renderParams[ShaderCtrlBit::normal] == 1){
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, normal));
    glEnableVertexAttribArray(3);
  }

  if(renderParams[ShaderCtrlBit::indexed] == 1){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Model->modelIndices.size() * sizeof(GLuint), &Model->modelIndices[0], GL_STATIC_DRAW);
  }
  GLenum errorLog = glGetError();
  return VAO;
}

void loadModelMaterial(const aiScene* scene, aiMesh* currentMesh, ModelComposite* Model){
  if(scene->HasMaterials()){
    aiColor4D ambientColor; 
    scene->mMaterials[currentMesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);
	  aiColor4D diffuseColor;
	  scene->mMaterials[currentMesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
	  aiColor4D specularColor;
	  scene->mMaterials[currentMesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);

    aiString ambientTexture;
    scene->mMaterials[currentMesh->mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_AMBIENT, 0), ambientTexture);
    aiString diffuseTexture;
    scene->mMaterials[currentMesh->mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), diffuseTexture);
    aiString specularTexture;
    scene->mMaterials[currentMesh->mMaterialIndex]->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), specularTexture);

    Model->materialBlock = {
      { ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a },
	    { diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a },
	    { specularColor.r, specularColor.g, specularColor.b, specularColor.a }
    };
  }  else {
    std::cerr << "No model materials present" << std::endl;
  }
}

void loadOpenGL_Faces(aiMesh* currentMesh, ModelComposite* Model){
  if(currentMesh->HasFaces()){
    for(unsigned int f = 0; f < currentMesh->mNumFaces; f++){
      unsigned int faceIndicesCount = currentMesh->mFaces[f].mNumIndices;
      for(unsigned int i = 0; i < faceIndicesCount; i++){
        unsigned int currentIndex = currentMesh->mFaces[f].mIndices[i];
        Model->modelIndices.push_back(currentIndex);
      }
    }
    Model->renderParams[ShaderCtrlBit::indexed] = 1;
  } else {
    std::cerr << "Mesh present without faces" << std::endl;
  }
}

void loadOpenGL_VertexPos(aiMesh* currentMesh, std::vector<std::array<GLfloat, 3>>* allVertexPos){
  if(currentMesh->HasPositions()){
    for(unsigned int v = 0; v < currentMesh->mNumVertices; v++){
      allVertexPos->push_back(
        { currentMesh->mVertices[v].x,
          currentMesh->mVertices[v].y,
          currentMesh->mVertices[v].z }
      );
    }
  } else {
    std::cerr << "No vertex positions present" << std::endl;
  }
}

void loadOpenGL_VertexColor(aiMesh* currentMesh, ModelComposite* Model, std::vector<std::array<GLfloat, 4>>* allVertexColors){
  if(currentMesh->HasVertexColors(0)){
    for(unsigned int v = 0; v < currentMesh->mNumVertices; v++){
      allVertexColors->push_back(
        { currentMesh->mColors[0][v].r,
          currentMesh->mColors[0][v].g,
          currentMesh->mColors[0][v].b,
          currentMesh->mColors[0][v].a }
      );
    }
    Model->renderParams[ShaderCtrlBit::color] = 1;
  } else {
    std::cout << "No vertex colors present, proceeding to generate at random..." << std::endl;
    srand(time(NULL));
    GLfloat randomColor_R, randomColor_G, randomColor_B;
    for(unsigned int c = 0; c < currentMesh->mNumVertices; c++){
      randomColor_R = static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX);
      randomColor_G = static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX);
      randomColor_B = static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX);
      allVertexColors->push_back( { randomColor_R, randomColor_G, randomColor_B, 0.5f } );
    }
    Model->renderParams[ShaderCtrlBit::color] = 1;
  }
}

void loadOpenGL_VertexTexCoord(aiMesh* currentMesh, ModelComposite* Model, std::vector<std::array<GLfloat, 2>>* allVertexTexCoord){
  if(currentMesh->HasTextureCoords(0)){
    for(unsigned int v = 0; v < currentMesh->mNumVertices; v++){
      allVertexTexCoord->push_back(
        { currentMesh->mTextureCoords[0][v].x,
          currentMesh->mTextureCoords[0][v].y }
      );
    }
    Model->renderParams[ShaderCtrlBit::texCoord] = 1;
  } else {
    std::cout << "No texture coordinates present" << std::endl;
    Model->renderParams[ShaderCtrlBit::texCoord] = 0;
  }
}

void loadOpenGL_VertexNormals(aiMesh* currentMesh, ModelComposite* Model, std::vector<std::array<GLfloat, 3>>* allVertexNormals){
  if(currentMesh->HasPositions()){
    for(unsigned int v = 0; v < currentMesh->mNumVertices; v++){
      allVertexNormals->push_back(
        { currentMesh->mNormals[v].x,
          currentMesh->mNormals[v].y,
          currentMesh->mNormals[v].z }
      );
    }
    Model->renderParams[ShaderCtrlBit::normal] = 1;
  } else {
    std::cerr << "No vertex positions present" << std::endl;
  }
}

void iterateNodes(const aiScene* scene, std::vector<ModelComposite>* MPerComponent){
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

    ModelComposite Model;
    unsigned int nodeMeshCount = currentNode->mNumMeshes;
    unsigned int* nodeMeshes = currentNode->mMeshes;
    aiMatrix4x4 relativePos = currentNode->mTransformation;
    aiNode* parentNode = currentNode->mParent;
    if(NULL != parentNode) relativePos *= parentNode->mTransformation;
    Model.relativePos = glm::mat4(
        { relativePos.a1, relativePos.b1, relativePos.c1, relativePos.d1,
        relativePos.a2, relativePos.b2, relativePos.c2, relativePos.d2,
        relativePos.a3, relativePos.b3, relativePos.c3, relativePos.d3,
        relativePos.a4, relativePos.b4, relativePos.c4, relativePos.d4 }
    );
    
    if(nodeMeshCount > 0){
      for(unsigned int m = 0; m < nodeMeshCount; m++){
        aiMesh* currentMesh = modelMeshes[nodeMeshes[m]];
        
        loadOpenGL_Faces(currentMesh, &Model);

        unsigned int meshVertexCount = currentMesh->mNumVertices;
        std::vector<std::array<GLfloat, 3>> allVertexPos;
        std::vector<std::array<GLfloat, 4>> allVertexColors;
        std::vector<std::array<GLfloat, 2>> allVertexTexCoord;
        std::vector<std::array<GLfloat, 3>> allVertexNormals;

        loadOpenGL_VertexPos(currentMesh, &allVertexPos);
        loadOpenGL_VertexColor(currentMesh, &Model, &allVertexColors);
        loadOpenGL_VertexTexCoord(currentMesh, &Model, &allVertexTexCoord);
        loadOpenGL_VertexNormals(currentMesh, &Model, &allVertexNormals);

        for(unsigned int i = 0; i < meshVertexCount; i++) Model.modelMeshes.push_back(
          { allVertexPos.at(i), allVertexColors.at(i), allVertexTexCoord.at(i), allVertexNormals.at(i) }
        );

        loadModelMaterial(scene, currentMesh, &Model);

        Model.VertexArray = loadModelData(&Model);
        Model.renderParams[ShaderCtrlBit::drawable] = 1;
        MPerComponent->push_back(Model);
      }
    } else {
      Model.VertexArray = 0;
      Model.renderParams[ShaderCtrlBit::drawable] = 0;
      MPerComponent->push_back(Model);
    }
  }
}

int assimpImportCPP(const std::string &pFile, std::vector<ModelComposite>* MPerComponent){

  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(pFile,
        aiProcess_CalcTangentSpace       | 
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType |
        // aiProcess_GenNormals |
        aiProcess_PreTransformVertices
  );

  if(! scene) {
    std::cout << "File import has failed due to error: " << importer.GetErrorString() << std::endl;
    return -1;
  } else 
    std::cout << "Imported File: " << pFile << std::endl;

  if(scene->HasMeshes()){
    iterateNodes(scene, MPerComponent);
  } else {
    std::cout << "Scene does not contain meshes" << std::endl;
    return -1;
  }

  return 0;
}
