#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

// From LoadData.cpp // Legacy

GLuint loadData(GLuint VAO, GLuint vertexCount, GLenum drawUsage, GLfloat* pos, GLfloat* color, GLfloat* normal, GLfloat* texCoord);
void loadIndices(GLuint VAO, GLuint indexCount, GLenum drawUsage, GLuint* index);

// From FileIO.cpp

const std::string getParentDir(const char* path);
char* readFile(const std::string& fileName);

// From LoadShaders.cpp

GLchar* readShaderFile(const char* nameOfShader);
GLuint compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
GLuint createShaderProg(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

// From LoadTextures.cpp

GLuint createTexture(const char* Filename);