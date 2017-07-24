#include <cmath>
#include <cstring>
#include <cstdlib>

#include <string>
#include <iostream>
#include <array>
#include <bitset>

#include <GL/glew.h>
#include <glm/glm.hpp>

// From LoadShaders.cpp

GLchar* readShaderFile(const char* nameOfShader);
GLuint compileShaders(const std::string& rootpath, const char* vertexShaderBaseName, const char* fragmentShaderBaseName);
GLuint compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

// From LoadTextures.cpp

GLuint createTexture(const char* filePath);
GLuint textureCheck(GLuint texture, std::string pathToFile);

// From Model3D.cpp

#include <vector>

#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Point {
    std::array<GLfloat, 3> pos;
    std::array<GLfloat, 4> color;
    std::array<GLfloat, 2> texCoord;
    std::array<GLfloat, 3> normal;
};

namespace ShaderCtrlBit {
    enum ShaderCtrlBit {
        color,
        texCoord
    };
};

struct ModelStatic {
    GLuint VertexArray;
    std::vector<Point> modelMeshes;
    std::vector<GLuint> modelIndices;

    std::bitset<2> renderParams;
};

int assimpImportCPP(const std::string& pFile);
int assimpImportCPP(const std::string& pFile, ModelStatic* Model);

int loadModelData(std::vector<Point> dataToLoad, std::vector<GLuint> dataIndices);
GLuint loadModelData(ModelStatic* Model);

// From ShaderCtrl.cpp

struct viewer3D_vert_uniformData {
	glm::mat4 worldMatrix;
	glm::mat4 localMatrix;
};

struct viewer3D_frag_uniformData {
	GLfloat ambientLightStrength;
	GLuint surfaceRenderMode;
};

struct viewer3D_ShaderObj {
    GLuint shaderProgID;
    viewer3D_vert_uniformData vert_uniformData;
    viewer3D_frag_uniformData frag_uniformData;
};

void viewer3D_UniformBlocks(GLuint shaderProgID, ModelStatic* Model);
void viewer3D_UniformBlocks(viewer3D_ShaderObj* ShaderObj, ModelStatic* Model);