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

struct PointTwo {
    GLfloat pos[3];
    GLfloat color[4];
    GLfloat texCoord[2];
    GLfloat normal[3];
};

struct ModelStatic {
    GLuint VertexArray;
    std::vector<Point> modelMeshes;
    std::vector<GLuint> modelIndices;

    enum renderEnum {
        VAttrib_color,
        VAttrib_texCoord
    };
    
    std::bitset<2> renderParams;
};

enum class VAttrib : std::size_t {
    color,
    texCoord
};

int assimpImportCPP(const std::string& pFile);
int assimpImportCPP(const std::string& pFile, ModelStatic* Model);

int loadModelData(std::vector<Point> dataToLoad, std::vector<GLuint> dataIndices);
GLuint loadModelData(ModelStatic* Model);
