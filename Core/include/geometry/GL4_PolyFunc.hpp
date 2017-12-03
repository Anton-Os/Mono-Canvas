#ifndef GEOMETRY_H
    #include "geometry/Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLY_FUNC_H
    class GL4_PolyFunc : public GL4_Object3D {
    public:
        void (*xEquation)(std::vector<float>* xVals);
        float (*yEquation)(float);
        float (*zEquation)(float, float);
        void reset();
        void gen_x();
        void gen_y();
        void gen_z();
        void createXI();
        void create();
        void drawXI(GLenum drawMode, GLuint drawCount);
        void draw(GLenum drawMode);
        void draw(GLenum drawMode, unsigned int drawCount);
    private:
        bool isIdx = false;
        unsigned int indexCount;
        std::vector<float> xVals;
        std::vector<float> yVals;
        std::vector<float> zVals;
        enum ptAttrib { X, Y, Z };
        std::bitset<3> xyzBits;
        enum feedParams { VAO, EBO, feedPos };
        unsigned int feed[3];
    };

#define POLY_FUNC_H
#endif