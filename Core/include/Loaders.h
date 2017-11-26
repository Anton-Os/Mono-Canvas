#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

// From LoadData.cpp // Legacy

GLuint loadData(GLuint VAO, GLuint vertexCount, GLenum drawUsage, GLfloat* pos, GLfloat* color, GLfloat* normal, GLfloat* texCoord);
void loadIndices(GLuint VAO, GLuint indexCount, GLenum drawUsage, GLuint* index);

// From FileIO.cpp

const std::string getParentDirectory(const char* path);
char* readFile(const char* fileName);

// From LoadShaders.cpp

GLchar* readShaderFile(const char* nameOfShader);
GLuint compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

// From LoadTextures.cpp

GLuint createTexture(const char* Filename);