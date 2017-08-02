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
        texCoord
    };
};

struct ModelStatic {
    GLuint VertexArray;
    std::vector<Point> modelMeshes;
    std::vector<GLuint> modelIndices;

    std::bitset<2> renderParams;
};

struct ModelComposite {
    GLuint VertexArray;
    std::vector<Point> modelMeshes;
    std::vector<GLuint> modelIndices;
    std::vector<std::array<GLfloat, 3>> cameraPos;

    std::bitset<2> renderParams;
};

int assimpImportCPP(const std::string& pFile);
int assimpImportCPP(const std::string& pFile, ModelStatic* Model);
int assimpImportCPP(const std::string &pFile, std::vector<ModelComposite>* MPerComponent);

int loadModelData(std::vector<Point> dataToLoad, std::vector<GLuint> dataIndices);
GLuint loadModelData(ModelStatic* Model);

// From ShaderCtrl.cpp

struct noBlocks_UniformData {
    glm::mat4 worldMatrix;
    glm::mat4 localMatrix;

    std::array<GLfloat, 4> defaultColor;
    GLuint surfaceRenderMode;
};


GLint noBlocks_worldMatrix(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms);
GLint noBlocks_localMatrix(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms);
GLint noBlocks_defaultColor(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms);
GLint noBlocks_surfaceRenderMode(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms);

int noBlocks_setUniforms(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms);
int noBlocks_setUniforms(GLuint shaderProgID, noBlocks_UniformData* noBlocks_Uniforms, ModelStatic* Model);

// From NoBlocks.cpp

namespace UniformIndex {
    enum UniformIndex {
        worldMatrix,
        localMatrix,
        defaultColor,
        surfaceRenderMode
    };
};

class NoBlocks {
public:
    NoBlocks(GLuint shaderProg){
        shaderProgID = shaderProg;
    }
    void worldMatrix(noBlocks_UniformData* noBlocks_Uniforms);
    void localMatrix(noBlocks_UniformData* noBlocks_Uniforms);
    void defaultColor(noBlocks_UniformData* noBlocks_Uniforms);
    void surfaceRenderMode(noBlocks_UniformData* noBlocks_Uniforms);
    
    void setUniforms(noBlocks_UniformData* noBlocks_Uniforms);
    void setUniforms(noBlocks_UniformData* noBlocks_Uniforms, ModelStatic* Model);
private:
    GLuint shaderProgID;
    std::vector<GLint> uniformLocation;
};
