#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLYFORM_GRID_H
class Polyform_Grid {
    public:
        Polyform_Grid(GL4_PolyFunc* polyFunc, float width_arg, unsigned int xCount_arg, 
                        float height_arg, unsigned int yCount_arg) {
            width = width_arg;
            xCount = xCount_arg;
            height = height_arg;
            yCount = yCount_arg;
            polyFunc->reset();
            create(polyFunc);
        }
        void create(GL4_PolyFunc* polyFunc);
    private:
        float width;
        unsigned int xCount;
        float height;
        unsigned int yCount;
    };
#define POLYFORM_GRID_H
#endif