#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLYFORM_CIRCLE_H
    class Polyform_Circle {
    public:
        Polyform_Circle(GL4_PolyAngles* polyAngles, float radiusArg, unsigned int intervalArg) {
            radius = radiusArg;
            interval = intervalArg;
            polyAngles->reset();
            create(polyAngles);
        }
        void create(GL4_PolyAngles* polyAngles);
    private:
        float radius;
        unsigned int interval;
    };

#define POLYFORM_CIRCLE_H
#endif