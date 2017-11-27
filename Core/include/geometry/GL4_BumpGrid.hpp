#ifndef GEOMETRY_H
    #include "geometry/Geometry.hpp"
    #define GEOMETRY_H
#endif

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