#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <bitset>

#include <GL/glew.h>
#include <glm/glm.hpp>

// From LoadShaders.cpp

GLchar* readShaderFile(const char* nameOfShader);
GLuint compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

// From LoadTextures.cpp

GLuint createTexture(const char* filePath);
GLuint textureCheck(GLuint texture, std::string pathToFile);

// From NoBlocks.cpp

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

namespace UniformIndex {
    enum UniformIndex {
        worldMatrix,
        localMatrix,
        defaultColor,
        surfaceRenderMode,
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
private:
    GLuint shaderProgID;
    std::vector<GLint> uniformLocation;
};