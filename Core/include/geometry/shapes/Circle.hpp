#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef CIRCLE_H
    class Circle {
    public:
        Circle(GL4_PolyAngles* polyAngles, float radiusArg, unsigned int intervalArg) {
            radius = radiusArg;
            interval = intervalArg;
            polyAngles->reset();
            create(polyAngles);
        }
        void create(GL4_PolyAngles* polyAngles);
    private:
        void anglFunc(std::vector<float>* anglVals);
        float xFunc(float angle);
        float yFunc(float angle);
        float zFunc(float angle);
        float radius;
        unsigned int interval;
    };

#define CIRCLE_H
#endif