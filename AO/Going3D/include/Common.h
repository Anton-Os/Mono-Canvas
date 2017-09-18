#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <string>
#include <iostream>
#include <array>
#include <bitset>

#include <GL/glew.h>
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL

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

struct Texel {
    GLuint height;
    GLuint width;
    std::array<GLfloat, 4> texColor;
};

struct MaterialBlock {
    std::array<GLfloat, 4> ambientColor;
    std::array<GLfloat, 4> diffuseColor;
    std::array<GLfloat, 4> specularColor;
};

struct LightSourceBlock {
    GLfloat radius;
    // std::array<GLfloat, 3> absoluteLocation;
    glm::vec3 absoluteLocation;
};

namespace ShaderCtrlBit {
    enum ShaderCtrlBit {
        color,
        texCoord,
        drawable,
        normal,
        indexed
    };
};

struct ModelComposite {
    GLuint VertexArray;
    std::vector<Point> modelMeshes;
    std::vector<Texel> textureEmb;
    std::vector<GLuint> modelIndices;
    glm::mat4 relativePos;
    MaterialBlock materialBlock;

    std::bitset<5> renderParams;
};

int assimpImportCPP(const std::string& pFile);
int assimpImportCPP(const std::string &pFile, std::vector<ModelComposite>* MPerComponent);

void genRandomColors(std::vector<std::array<GLfloat, 4>>* allVertexColors, GLfloat alphaFactor);
void genRandomColors(std::vector<std::array<GLfloat, 4>>* allVertexColors, GLuint vertexCount, GLfloat alphaFactor);
std::array<GLfloat, 4> genRandomColors(GLfloat alphaFactor);

GLuint loadModelData(ModelComposite* Model);
GLuint loadModelData(ModelComposite* Model, std::bitset<5> renderParams);

// From Geometry.cpp

int createSphere(ModelComposite* sphereModel, GLfloat radius, GLuint sliceCount, GLuint stackCount);
// int createSphere(ModelComposite* sphereModel, GLfloat radius, GLfloat sliceCount, GLfloat stackCount);
unsigned int createRevLine(GLuint length, std::array<GLfloat, 2> pos, std::array<GLfloat, 2> change, std::array<GLfloat, 6> colorRange);

#include "ShaderCtrl.h"