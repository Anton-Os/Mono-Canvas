#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <array>

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

struct PointTwo {
    GLfloat pos[3];
    GLfloat color[4];
    GLfloat texCoord[2];
    GLfloat normal[3];
};

struct ModelStatic {
    const std::string& pFile;
    GLuint VertexArray;
    std::vector<Point> modelMeshes;
    std::vector<GLuint> modelIndices;
};

int assimpImportCPP(const std::string& pFile);
int assimpImportCPP(ModelStatic* Model);

int loadModelData(std::vector<Point> dataToLoad, std::vector<GLuint> dataIndices);
GLuint loadModelData(ModelStatic* Model);
