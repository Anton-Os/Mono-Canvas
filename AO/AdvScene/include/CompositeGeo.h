#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdlib>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GL4_Sphere {
public:
    GL4_Sphere(GLuint radius, GLuint sliceCount, GLuint stackCount){
        create(radius, sliceCount, stackCount);
    }
    enum feedParams { VAO, EBO, feedPos, feedTexCoord };
    GLuint feed[4];
    glm::mat4 relMatrix;
    void create(GLuint radius, GLuint sliceCount, GLuint stackCount);
    void draw();
    void draw(GLenum drawMode);
    void drawFixed(GLenum drawMode, GLuint indexCount);
    void drawPart(GLenum drawMode, GLuint part, GLuint whole);
private:
    GLuint vertexCount;
};

class GL4_BumpGrid {
public:
    GL4_BumpGrid(GLfloat smoothness, GLuint xDimension, GLuint stackCount, GLuint yDimension, GLuint sliceCount){
        create(smoothness, xDimension, stackCount, yDimension, sliceCount);
    }
    enum feedParams { VAO, EBO, feedPos, feedTexCoord, feedNormal };
    GLuint feed[5];
    glm::mat4 relMatrix;
    void create(GLfloat smoothness, GLuint xDimension, GLuint stackCount, GLuint yDimension, GLuint sliceCount);
    void draw();
private:
    GLuint vertexCount;
};