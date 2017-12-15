#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef GL4_ENTITY_H
    #include "geometry/GL4_Entity.hpp"
#endif

#ifndef POLY_FUNC_H
    class GL4_PolyFunc : public GL4_Entity {
    public:
        void (*xSequence)(std::vector<float>* xVals);
        float (*yEquation)(float);
        float (*zEquation)(float, float);
        void reset();
        void gen_x();
        void gen_y();
        void gen_z();
        void createXI();
        void create();
    private:
        std::vector<float> xVals;
        std::vector<float> yVals;
        std::vector<float> zVals;
        enum ptAttrib { X, Y, Z };
        std::bitset<3> xyzBits;
    };

#define POLY_FUNC_H
#endif
