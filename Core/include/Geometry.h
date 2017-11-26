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
    void index(GLvoid* data, GLint dataSize);
    void draw(GLenum drawMode, GLuint drawCount);
    void drawIdx(GLenum drawMode, GLuint indexCount);
private:
    enum feedParams {VAO, feedPos};
    GLuint feed[2];
};

class GL4_Object3D {
public:
    glm::mat4 relMatrix;
    GLuint get_vertexCount(){ return vertexCount; }
    // drawXI();
    // drawXI(GLenum drawMode);
    // drawFixedXI(GLenum drawMode, GLuint vertexCount);
    // drawPartXI(GLenum drawMode, GLuint part, GLuint whole);
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

class GL4_Grid : public GL4_Object3D {
public:
    GL4_Grid(GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount){
        if(rowCount == colCount) isSquare = true;
        create(xDimension, rowCount, yDimension, colCount);
    }
    enum feedParams { VAO, EBO, feedPos, feedTexCoord };
    GLuint feed[5];
    void create(GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount);
    void map(std::vector<GLfloat>* posAccum);
    void map(std::vector<GLuint>* indexAccum);
    bool get_isSquare(){ return isSquare; }
    void draw();
    void draw(GLenum drawMode);
    void drawXI(GLenum drawMode);
    void drawFixed(GLenum drawMode, GLuint indexCount);
private:
    bool isSquare = false;
    GLuint indexCount;
};

class GL4_BumpGrid : public GL4_Object3D {
public:
    GL4_BumpGrid(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount){
        if(rowCount == colCount) isSquare = true;
        create(rise, xDimension, rowCount, yDimension, colCount);
    }
    enum feedParams {VAO, EBO, feedPos, feedTexCoord, feedNormal};
    GLuint feed[5];
    void create(GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount);
    void create(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount);
    void map(std::vector<GLfloat>* posAccum);
    void map(std::vector<GLuint>* indexAccum);
    bool get_isSquare(){ return isSquare; }
    void gen_midPointQ(std::vector<MidPointQuad>* midPoints);
    void gen_midPointT(std::vector<MidPointTrig>* midPoints);
    void gen_midPoint45(std::vector<MidPoint45>* midPoints);
    void draw();
    void draw(GLenum drawMode);
    void drawXI(GLenum drawMode);
    void drawFixed(GLenum drawMode, GLuint indexCount);
private:
    bool isSquare = false;
    GLuint indexCount;
};

struct Hexagon {
    float sixProx[18];
    float midPoint[3];
};

Hexagon createHex(float size);
Hexagon createHex(float size, float initPos[]);

// Hexagon Vertical Subdivision by 4
struct HexagonIdx12 {
    float sixProx[18];
    float midPoint[3];
    std::array<unsigned int, 12> indices;
};

HexagonIdx12 createHexIdx12(float size, float initPos[], unsigned short int mode);

class GL4_HexGrid : public GL4_Object3D {
public:
    GL4_HexGrid(float hexSize, GLuint rowCount, GLuint colCount){
        if(rowCount == colCount) isSquare = true;
        create(hexSize, rowCount, colCount);
    }
    enum feedParams { VAO, EBO, feedPos, feedTexCoord };
    GLuint feed[4];
    void create(float hexSize, GLuint rowCount, GLuint colCount);
    void map(std::vector<GLfloat>* posAccum);
    void map(std::vector<GLuint>* indexAccum);
    bool get_isSquare(){ return isSquare; }
    void draw();
    void draw(GLenum drawMode);
    void drawXI(GLenum drawMode);
    void drawFixed(GLenum drawMode, GLuint indexCount);
private:
    bool isSquare = false;
    GLuint indexCount;
};

class GL4_PolyFunc : public GL4_Object3D {
public:
    float (*xEquasion)();
    float (*yEquasion)(float);
    float (*zEquasion)(float, float);
    std::vector<float> xVals;
    std::vector<float> yVals;
    std::vector<float> zVals;
    void gen_x(std::vector<float>* xVals, float interval, unsigned int reps);
    void gen_x(float interval, unsigned int reps);
    void gen_y();
};
