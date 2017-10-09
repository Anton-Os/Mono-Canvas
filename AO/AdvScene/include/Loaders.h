#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

// From LoadShaders.h

GLchar* readShaderFile(const char* nameOfShader);
GLuint compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

// From LoadData.h

/* struct gl4_BufferFeed {
    GLenum target;
    // GLuint buffer;
    GLfloat* data;
    GLuint setOf;
};

class gl4_BufferFeeder {
public:
    GLuint VAO;
    std::vector<GLuint> buffer;
    GLuint vertexCount;
    GLuint indexCount;
}; */

GLuint loadData(GLuint VAO, GLuint vertexCount, GLenum drawUsage, GLfloat* pos, GLfloat* color, GLfloat* normal, GLfloat* texCoord);
void loadIndices(GLuint VAO, GLuint indexCount, GLenum drawUsage, GLuint* index);