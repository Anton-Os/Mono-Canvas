#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <array>
#include <limits>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GL4_Object {
public:
    glm::mat4 relMatrix;
protected:
    GLuint vertexCount;
};

class GL4_Sphere : public GL4_Object {
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

struct MidPointQ {
    float pos[3];
    float fourProx[12];
};

struct MidPointT {
    float pos[3];
    float fourProx[9];
};

class GL4_BumpGrid : public GL4_Object {
public:
    GL4_BumpGrid(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount){
        // create(rise, xDimension, rowCount, yDimension, colCount);
        create_v3(rise, xDimension, rowCount, yDimension, colCount);
    }
    enum feedParams {VAO, EBO, feedPos, feedTexCoord, feedNormal};
    GLuint feed[5];
    void create(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount);
    void create_v2(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount);
    void create_v3(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount);
    void map(std::vector<GLfloat>* posAccum);
    void map(std::vector<GLuint>* indexAccum);
    void get_midPoint(std::vector<MidPointQ>* midPoints){ midPoints->swap(midPointQ_Accum); }
    void gen_midPointQuads(std::vector<MidPointQ>* midPoints);
    void draw();
    void draw(GLenum drawMode);
    void drawFixed(GLenum drawMode, GLuint indexCount);
private:
    GLuint indexCount;
    std::vector<MidPointQ> midPointQ_Accum;
};