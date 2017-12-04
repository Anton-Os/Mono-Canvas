#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <array>
#include <limits>
#include <climits>
#include <bitset>
#include <algorithm>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GL4_Object3D {
public:
    glm::mat4 relMatrix = glm::mat4(1);
    GLuint get_vertexCount(){ return vertexCount; }
    void drawXI(GLenum drawMode){
        glBindVertexArray(GL4_Object3D::VAO);
        glDrawArrays(drawMode, 0, GL4_Object3D::vertexCount);
        glBindVertexArray(0);
    }
    void drawFixedXI(GLenum drawMode, GLuint drawCount){
        glBindVertexArray(GL4_Object3D::VAO);
        if(drawCount > GL4_Object3D::vertexCount) glDrawArrays(drawMode, 0, GL4_Object3D::vertexCount);
        else glDrawArrays(drawMode, 0, drawCount);
        glBindVertexArray(0);
    }
    void drawPartXI(GLenum drawMode, GLuint part, GLuint whole){
        glBindVertexArray(GL4_Object3D::VAO);
        if(part > whole) glDrawArrays(drawMode, 0, GL4_Object3D::vertexCount);
        else glDrawArrays(drawMode, 0, GL4_Object3D::vertexCount / whole * part);
        glBindVertexArray(0);
    }
protected:
    GLuint VAO;
    GLuint posBff;
    GLuint vertexCount = 0;
};