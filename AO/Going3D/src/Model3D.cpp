#include "Common.h"
// #include "Assimp.h"

int loadModelData(std::vector<Point> dataToLoad, std::vector<GLuint> dataIndices){
  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ARRAY_BUFFER, dataToLoad.size() * sizeof(Point), &dataToLoad[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, pos));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, color));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, texCoord));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, normal));
  glEnableVertexAttribArray(3);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataIndices.size() * sizeof(GLuint), &dataIndices[0], GL_STATIC_DRAW);

  GLenum errorLog = glGetError();
  return 0;
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
  if(Model->renderParams[Model->VAttrib_texCoord] == 0){
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, texCoord));
    glEnableVertexAttribArray(2);
  }
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, normal));
  glEnableVertexAttribArray(3);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, Model->modelIndices.size() * sizeof(GLuint), &Model->modelIndices[0], GL_STATIC_DRAW);

  GLenum errorLog = glGetError();
  return VAO;
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
  std::vector<GLuint> allIndices;
  
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
      unsigned int meshFaceCount = modelMeshes[i]->mNumFaces;
      aiFace* meshFaces = modelMeshes[i]->mFaces;

      for(unsigned int f = 0; f < meshFaceCount; f++){
        for(unsigned int i = 0; i < meshFaces[f].mNumIndices; i++){
          unsigned int currentIndex = meshFaces[f].mIndices[i];
          allIndices.push_back(currentIndex);
        }
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

      Point currentMeshData;
      for(unsigned int md = 0; md < meshVertexCount; md++){
        currentMeshData.pos = allVertexPos.at(md);
        currentMeshData.color = allVertexColors.at(md);
        currentMeshData.texCoord = allVertexTexCoord.at(md);
        currentMeshData.normal = allVertexNormals.at(md);

        allMeshes.push_back(currentMeshData);
      }
    }
  } else {
      std::cout << "Scene does not contain meshes" << std::endl;
      return -1;
  }

  loadModelData(allMeshes, allIndices);

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

    unsigned int meshesCount = scene->mNumMeshes;
    std::cout << "Number of meshes present in scene is " << meshesCount << std::endl;
    aiNode* currentNode = scene->mRootNode;
    aiMesh** modelMeshes = scene->mMeshes;

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
        for(unsigned int c = 0; c < meshVertexCount; c++){
            // allVertexColors.push_back( {0.2588f, 0.5254f, 0.9568f, 1.0} ); // Soothing blue color
            allVertexColors.push_back( {0.9607f, 0.6862f, 0, 0.8} ); // Yellowish color
        }
        Model->renderParams[ShaderCtrlBit::color] = 1;
      }

      if(modelMeshes[i]->HasTextureCoords(0)){
        std::cout << "Mesh # " << i << " contains texture coordinates" << std::endl;
        for(unsigned int tc = 0; tc < meshVertexCount; tc++){
            float tcX = modelMeshes[i]->mTextureCoords[0][tc].x;
            float tcY = modelMeshes[i]->mTextureCoords[0][tc].y;
            allVertexTexCoord.push_back( {tcX, tcY} );
        }
        Model->renderParams[Model->VAttrib_texCoord] = 0;
      } else {
        std::cout << "Mesh # " << i << " does not contain texture coordinates" << std::endl;
        for(unsigned int tc = 0; tc < meshVertexCount; tc++){
            allVertexTexCoord.push_back( {0.0, 0.0} );
        }
        Model->renderParams[Model->VAttrib_texCoord] = 1;
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

  std::cout << Model->renderParams << std::endl;
  
  return 0;
}
