#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLYFORM_RUBIKS_H
    class Polyform_Rubiks {
    public:
        Polyform_Rubiks(GL4_PolyFunc* polyFunc, Polyform_Box* polyBox, float xCountArg, float yCountArg, float zCountArg){
            xCount = xCountArg;
            yCount = yCountArg;
            zCount = zCountArg;
            create(polyFunc, polyBox);
        }
        void create(GL4_PolyFunc* polyFunc, Polyform_Box* polyBox);
    private:
        float xCount;
        float yCount;
        float zCount;
    };
#define POLYFORM_RUBIKS_H
#endif