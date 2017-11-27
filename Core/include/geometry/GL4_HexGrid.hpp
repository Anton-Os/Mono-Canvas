#ifndef GEOMETRY_H
    #include "geometry/Geometry.hpp"
    #define GEOMETRY_H
#endif

#include <algorithm>

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