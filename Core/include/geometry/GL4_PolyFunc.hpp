#ifndef GEOMETRY_H
    #include "geometry/Geometry.hpp"
    #define GEOMETRY_H
#endif

class GL4_PolyFunc : public GL4_Object3D {
public:
    void (*xEquasion)(std::vector<float>* xVals);
    float (*yEquasion)(float);
    float (*zEquasion)(float, float);
    std::vector<float> xVals;
    std::vector<float> yVals;
    std::vector<float> zVals;
    void gen_x();
    void gen_y();
    void gen_z();
    void create();
    void draw(GLenum drawMode, GLuint drawCount);
private:
    enum ptAttrib { X, Y, Z };
    std::bitset<3> xyzBits;
    enum feedParams { VAO, feedPos };
    unsigned int feed[2];
};