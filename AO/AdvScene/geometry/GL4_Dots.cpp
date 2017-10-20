#include "Geometry.h"

void GL4_Dots::init(){
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    GL4_Dots::feed[GL4_Dots::VAO] = VAO;
    GLuint VBO;
    glGenBuffers(1, &VBO);
    GL4_Dots::feed[GL4_Dots::feedPos] = VBO;
}

void GL4_Dots::create(GLvoid* data, GLint dataSize){
    glBindVertexArray(GL4_Dots::feed[GL4_Dots::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_Dots::feed[GL4_Dots::feedPos]);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void GL4_Dots::create(GLvoid* data, GLint dataSize, GLsizei stride, const GLvoid* offset){
    glBindVertexArray(GL4_Dots::feed[GL4_Dots::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_Dots::feed[GL4_Dots::feedPos]);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void GL4_Dots::draw(float pointSize, GLuint drawCount){
    glPointSize(pointSize);
    glBindVertexArray(GL4_Dots::feed[GL4_Dots::VAO]);
    glDrawArrays(GL_POINTS, 0, drawCount);
    glBindVertexArray(0);
}