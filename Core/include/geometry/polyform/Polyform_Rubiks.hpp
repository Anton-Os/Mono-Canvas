#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLYFORM_RUBIKS_H
    class Polyform_Rubiks {
    public:
        Polyform_Rubiks(unsigned int xCountArg, unsigned int yCountArg, unsigned int zCountArg){
            xCount = xCountArg;
            yCount = yCountArg;
            zCount = zCountArg;
        }
        Polyform_Rubiks(GL4_PolyFunc* polyFunc, Polyform_Box* polyBox, unsigned int xCountArg, unsigned int yCountArg, unsigned int zCountArg){
            xCount = xCountArg;
            yCount = yCountArg;
            zCount = zCountArg;
            create(polyFunc, polyBox);
        }
        void createXI(GL4_PolyFunc* polyFunc, Polyform_Box* polyBox);
        void create(GL4_PolyFunc* polyFunc, Polyform_Box* polyBox);
    private:
        unsigned int xCount;
        unsigned int yCount;
        unsigned int zCount;
    };
#define POLYFORM_RUBIKS_H
#endif