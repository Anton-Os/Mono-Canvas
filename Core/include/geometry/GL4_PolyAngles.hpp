#ifndef GEOMETRY_H
    #include "geometry/Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLY_ANGLES_H
    class GL4_PolyAngles : public GL4_Object3D {
    public:
        void (*anglEquation)(std::vector<float>* anglVals);
        unsigned int (*idxEquation)(std::vector<unsigned int>* idxVals);
        float (*xEquation)(float);
        float (*yEquation)(float);
        float (*zEquation)(float);
        void reset();
        void gen_angl();
        void gen_x();
        void gen_y();
        void gen_z();
        void createXI();
        void create();
        void map(std::vector<float>* posAccum);
        void draw(GLenum drawMode);
        void draw(GLenum drawMode, unsigned int drawCount);
    private:
        unsigned int idxBff;
        unsigned int indexCount;
        bool isIdx = false;
        bool isFed = false;
        std::vector<float> angles;
        std::vector<float> xVals;
        std::vector<float> yVals;
        std::vector<float> zVals;
        enum ptAttrib { Angl, X, Y, Z };
        std::bitset<4> xyzBits;
    };

#define POLY_ANGLES_H
#endif