#include "Geometry.h"

void GL4_DataSet::init(){
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    GL4_DataSet::feed[GL4_DataSet::VAO] = VAO;
    GLuint VBO;
    glGenBuffers(1, &VBO);
    GL4_DataSet::feed[GL4_DataSet::feedPos] = VBO;
}

void GL4_DataSet::create(GLvoid* data, GLint dataSize){
    glBindVertexArray(GL4_DataSet::feed[GL4_DataSet::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_DataSet::feed[GL4_DataSet::feedPos]);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void GL4_DataSet::create(GLvoid* data, GLint dataSize, GLsizei stride, const GLvoid* offset){
    glBindVertexArray(GL4_DataSet::feed[GL4_DataSet::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_DataSet::feed[GL4_DataSet::feedPos]);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

/* void GL4_DataSet::draw(float pointSize, GLuint drawCount){
    glPointSize(pointSize);
    glBindVertexArray(GL4_DataSet::feed[GL4_DataSet::VAO]);
    glDrawArrays(GL_POINTS, 0, drawCount);
    glBindVertexArray(0);
} */

void GL4_DataSet::draw(GLenum drawMode, GLuint drawCount){
    glBindVertexArray(GL4_DataSet::feed[GL4_DataSet::VAO]);
    glDrawArrays(drawMode, 0, drawCount);
    glBindVertexArray(0);
}