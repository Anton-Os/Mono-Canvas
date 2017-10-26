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

struct MidPointTrig {
    float pos[3];
    float threeProx[9];
};

struct MidPointQuad {
    float pos[3];
    float fourProx[12];
};

struct MidPoint45 {
    float pos[3];
    float fourProx[12];

    float t1[3];
    short unsigned int threeIndex1[3];

    float t2[3];
    short unsigned int threeIndex2[3];
};

class GL4_DataSet {
public:
    GL4_DataSet(GLvoid* data, GLint dataSize){
        init();
        create(data, dataSize);
    }
    GL4_DataSet(GLvoid* data, GLint dataSize, GLsizei stride, const GLvoid* offset){
        init();
        create(data, dataSize, stride, offset);
    }
    GL4_DataSet(GLint attribCount, GLvoid* data, GLint dataSize){
        init();
        create(attribCount, data, dataSize);
    }
    GL4_DataSet(GLint attribCount, GLvoid* data, GLint dataSize, GLsizei stride, const GLvoid* offset){
        init();
        create(attribCount, data, dataSize, stride, offset);
    }
    void init();
    void create(GLvoid* data, GLint dataSize);
    void create(GLint attribCount, GLvoid* data, GLint dataSize);
    void create(GLvoid* data, GLint dataSize, GLsizei stride, const GLvoid* offset);
    void create(GLint attribCount, GLvoid* data, GLint dataSize, GLsizei stride, const GLvoid* offset);
    void draw(GLenum drawMode, GLuint drawCount);
private:
    enum feedParams {VAO, feedPos};
    GLuint feed[2];
};

class GL4_Object3D {
public:
    glm::mat4 relMatrix;
protected:
    GLuint vertexCount;
};

class GL4_Sphere : public GL4_Object3D {
public:
    GL4_Sphere(GLuint radius, GLuint sliceCount, GLuint stackCount){
        create(radius, sliceCount, stackCount);
    }
    enum feedParams {VAO, EBO, feedPos, feedTexCoord};
    GLuint feed[4];
    void create(GLuint radius, GLuint sliceCount, GLuint stackCount);
    void draw();
    void draw(GLenum drawMode);
    void drawFixed(GLenum drawMode, GLuint indexCount);
    void drawPart(GLenum drawMode, GLuint part, GLuint whole);
};

class GL4_BumpGrid : public GL4_Object3D {
public:
    GL4_BumpGrid(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount){
        create(rise, xDimension, rowCount, yDimension, colCount);
    }
    enum feedParams {VAO, EBO, feedPos, feedTexCoord, feedNormal};
    GLuint feed[5];
    void create(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount);
    void map(std::vector<GLfloat>* posAccum);
    void map(std::vector<GLuint>* indexAccum);
    void gen_midPointQ(std::vector<MidPointQuad>* midPoints);
    void gen_midPointT(std::vector<MidPointTrig>* midPoints);
    void gen_midPoint45(std::vector<MidPoint45>* midPoints);
    void draw();
    void draw(GLenum drawMode);
    void drawFixed(GLenum drawMode, GLuint indexCount);
private:
    GLuint indexCount;
};

class GL4_RigidLine : public GL4_Object3D {
public:
    GL4_RigidLine(GLfloat rise, GLuint segCount, GLfloat xLength, GLfloat xVariance){
        create(rise, segCount, xLength, xVariance); 
    }
    GL4_RigidLine(GLfloat rise, GLfloat thickness, GLuint segCount, GLfloat xLength, GLfloat xVariance){
        create(rise, thickness, segCount, xLength, xVariance); 
    }
    enum feedParams {VAO, EBO, feedPos};
    GLuint feed[3];
    void create(GLfloat rise, GLuint segCount, GLfloat xLength, GLfloat xVariance);
    void create(GLfloat rise, GLfloat thickness, GLuint segCount, GLfloat xLength, GLfloat xVariance);
    void draw();
    void draw(GLenum drawMode);
    void drawXI(GLenum drawMode);
    void drawFixed(GLenum drawMode, GLuint indexCount);
    void drawXI(GLenum drawMode, GLuint indexCount);
    GLfloat get_length(){ return length; }
private:
    GLfloat length = 0.0;
    GLuint indices = 0; 
};