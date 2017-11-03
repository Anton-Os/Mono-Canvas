#include "Loaders.h"

GLuint loadData(GLuint VAO, GLuint vertexCount, GLenum drawUsage, GLfloat* pos, GLfloat* color, GLfloat* normal, GLfloat* texCoord){
  glBindVertexArray(VAO);
  GLuint VBOs[4];
  glGenBuffers(4, VBOs);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  GLuint vAttrib = 0;

  if(nullptr != pos){
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[vAttrib]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat), pos, drawUsage);
    glVertexAttribPointer(vAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(vAttrib);
    // std::cout << "pos attrib location: " << vAttrib << std::endl;
    vAttrib++;
  }
  if(nullptr != color){
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[vAttrib]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat), color, drawUsage);
    glVertexAttribPointer(vAttrib, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(vAttrib);
    std::cout << "color attrib location: " << vAttrib << std::endl;
    vAttrib++;
  }
  if(nullptr != normal){
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[vAttrib]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat), normal, drawUsage);
    glVertexAttribPointer(vAttrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(vAttrib);
    std::cout << "normal attrib location: " << vAttrib << std::endl;
    vAttrib++;
  }
  if(nullptr != texCoord){
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[vAttrib]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat), texCoord, drawUsage);
    glVertexAttribPointer(vAttrib, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(vAttrib);
    std::cout << "texCoord attrib location: " << vAttrib << std::endl;
    vAttrib++;
  }
  glBindVertexArray(0);
  return vAttrib;
}

void loadIndices(GLuint VAO, GLuint indexCount, GLenum drawUsage, GLuint* index){
  glBindVertexArray(VAO);
  GLuint EBO;
  glGenBuffers(1, &EBO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), index, drawUsage);

  glBindVertexArray(0);
}