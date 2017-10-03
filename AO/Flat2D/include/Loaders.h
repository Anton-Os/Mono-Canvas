#include <iostream>
#include <string>
#include <vector>

#include <boost/dynamic_bitset.hpp>
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

class GL4_BufferFeed {
public:
    std::vector<GLuint> VBO;
    std::vector<std::string> name;
    std::vector<GLenum> target;
    std::vector<GLenum> usage;
    std::vector<GLsizeiptr> size;
    std::vector<GLvoid*> data;
    void init(GLuint buffFeedsCount);
    void cycle();
};

class GL4_VAttribFeed {
public:    
    std::vector<GLuint> VBO;
    std::vector<GLuint> attribID;
    std::vector<GLubyte> compCount;
    std::vector<GLenum> dataType;
    std::vector<GLboolean> isNrm;
    void init(GLuint vAttribCount);
    void cycle();
    // void init(std::bitset< vAttribBits);
};

class GL4_BufferFeeder {
public:
    GL4_BufferFeeder(GLuint vao, GLuint buffFeedsCount){
        GL4_BufferFeeder::VAO = vao;
        bufferFeed.init(buffFeedsCount);
    }
    /* GL4_BufferFeeder(GLuint buffFeedsCount){
        glGenVertexArrays(1, &this.VAO);
        glBindVertexArray(this.VAO);
        bufferFeed.init(buffFeedsCount);
    } */
    GLuint VAO;
    GL4_BufferFeed bufferFeed;
    GL4_VAttribFeed vAttribFeed;
    // void init();
};

GLuint loadData(GLuint VAO, GLuint vertexCount, GLenum drawUsage, GLfloat* pos, GLfloat* color, GLfloat* normal, GLfloat* texCoord);
void loadIndices(GLuint VAO, GLuint indexCount, GLenum drawUsage, GLuint* index);