#ifndef GEOMETRY_H
    #include "geometry/Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLY_ANGLES_H
    class GL4_PolyAngles : public GL4_Object3D {
    public:
        void (*genAngles)(std::vector<float>* angles);
        float (*xEquation)(float);
        float (*yEquation)(float);
        float (*zEquation)(float);
        void reset();
        void gen_x();
        void gen_y();
        void gen_z();
        void createXI();
        void create();
        void drawXI(GLenum drawMode, GLuint drawCount);
        void draw(GLenum drawMode);
    private:
        unsigned int indexCount;
        std::vector<float> xVals;
        std::vector<float> yVals;
        std::vector<float> zVals;
        enum ptAttrib { X, Y, Z };
        std::bitset<3> xyzBits;
        enum feedParams { VAO, EBO, feedPos };
        unsigned int feed[3];
    };

#define POLY_ANGLES_H
#endif