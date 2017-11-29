#ifndef GEOMETRY_H
    #include "geometry/Geometry.hpp"
    #define GEOMETRY_H
#endif

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
