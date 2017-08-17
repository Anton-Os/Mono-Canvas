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
        texCoord,
        drawable
    };
};

struct ModelStatic {
    GLuint VertexArray;
    std::vector<Point> modelMeshes;
    std::vector<GLuint> modelIndices;

    std::bitset<3> renderParams;
};

struct ModelComposite {
    GLuint VertexArray;
    GLuint currentTexture;
    std::vector<Point> modelMeshes;
    std::vector<GLuint> modelIndices;
    glm::mat4 relativePos;

    std::bitset<3> renderParams;
};

int assimpImportCPP(const std::string& pFile);
int assimpImportCPP(const std::string& pFile, ModelStatic* Model);
int assimpImportCPP(const std::string &pFile, std::vector<ModelComposite>* MPerComponent);

int loadModelData(std::vector<Point> dataToLoad, std::vector<GLuint> dataIndices);
GLuint loadModelData(ModelStatic* Model);

// From ShaderCtrl

namespace UniformIndex {
    enum UniformIndex {
        worldMatrix,
        localMatrix,
        defaultColor,
        surfaceRenderMode,
    };
};

class AnyShader {
protected:
    GLuint shaderProgID;
    std::vector<GLint> uniformLocation;
};

struct noBlocks_UniformData {
    glm::mat4 worldMatrix;
    glm::mat4 localMatrix;

    std::array<GLfloat, 4> defaultColor;
    GLuint surfaceRenderMode;
};

class NoBlocks : public AnyShader {
public:
    NoBlocks(GLuint shaderProg){
        shaderProgID = shaderProg;
    }
    void worldMatrix(noBlocks_UniformData* noBlocks_Uniforms);
    void localMatrix(noBlocks_UniformData* noBlocks_Uniforms);
    void defaultColor(noBlocks_UniformData* noBlocks_Uniforms);
    void surfaceRenderMode(noBlocks_UniformData* noBlocks_Uniforms);
    
    void setUniforms(noBlocks_UniformData* noBlocks_Uniforms);
};

struct litEnv_MaterialBlock {
    std::array<GLfloat, 4> ambientColor;
    std::array<GLfloat, 4> diffuseColor;
    std::array<GLfloat, 4> specularColor;
};

struct litEnv_LightSourceBlock {
    GLfloat intensity;
    GLfloat radius;
    std::array<GLfloat, 4> absoluteLocation;
};

struct litEnv_UniformData {
    glm::mat4 worldMatrix;
    glm::mat4 localMatrix;

    litEnv_MaterialBlock materialBlock;
    litEnv_LightSourceBlock lightSourceBlock;
};

class LitEnv : public AnyShader {
public:
    LitEnv(GLuint shaderProg){
        shaderProgID = shaderProg;
    }

    void worldMatrix(litEnv_UniformData* litEnv_Uniforms);
    void localMatrix(litEnv_UniformData* litEnv_Uniforms);
    void materialBlock(litEnv_UniformData* litEnv_Uniforms);
    void lightSourceBlock(litEnv_UniformData* litEnv_Uniforms);

    void setUniforms(litEnv_UniformData* litEnv_Uniforms);
};