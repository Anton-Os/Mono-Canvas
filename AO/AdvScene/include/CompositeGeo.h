#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdlib>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GL4_Object {
public:
    glm::mat4 relMatrix;
protected:
    GLuint vertexCount;
};

class GL4_Sphere : GL4_Object {
public:
    GL4_Sphere(GLuint radius, GLuint sliceCount, GLuint stackCount){
        create(radius, sliceCount, stackCount);
    }
    enum feedParams { VAO, EBO, feedPos, feedTexCoord };
    GLuint feed[4];
    void create(GLuint radius, GLuint sliceCount, GLuint stackCount);
    void draw();
    void draw(GLenum drawMode);
    void drawFixed(GLenum drawMode, GLuint indexCount);
    void drawPart(GLenum drawMode, GLuint part, GLuint whole);
};

class GL4_BumpGrid : public GL4_Object {
public:
    GL4_BumpGrid(GLfloat smoothness, GLuint xDimension, GLuint stackCount, GLuint yDimension, GLuint sliceCount){
        create(smoothness, xDimension, stackCount, yDimension, sliceCount);
    }
    enum feedParams { VAO, EBO, feedPos, feedTexCoord, feedNormal };
    GLuint feed[5];
    void create(GLfloat smoothness, GLuint xDimension, GLuint stackCount, GLuint yDimension, GLuint sliceCount);
    void draw();
    void draw(GLenum drawMode);
    void drawFixed(GLenum drawMode, GLuint indexCount);
};