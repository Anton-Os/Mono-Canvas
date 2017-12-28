#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLY_FUNC_H
    #include "geometry/polybase/GL4_PolyFunc.hpp"
#endif

#ifndef POLY_BOX_H
    #include "geometry/polyform/Polyform_Box.hpp"
#endif

#ifndef POLYFORM_RUBIKS_H
    struct Polyform_Rubiks_Meta {
        unsigned int xCount;
        unsigned int yCount;
        unsigned int zCount;
    };

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
        Polyform_Rubiks(GL4_PolyFunc* polyFunc, float length, float width, float height, Polyform_Box* polyBox, unsigned int xCountArg, unsigned int yCountArg, unsigned int zCountArg){
            xCount = xCountArg;
            yCount = yCountArg;
            zCount = zCountArg;
            create(polyFunc, length, width, height);
        }
        void createXI(GL4_PolyFunc* workspace, Polyform_Box* polyBox);
        void create(GL4_PolyFunc* polyFunc, float length, float width, float height);
        void create(GL4_PolyFunc* polyFunc, Polyform_Box* polyBox);
        void exportMeta(Polyform_Rubiks_Meta* metaData);
    private:
        unsigned int xCount;
        unsigned int yCount;
        unsigned int zCount;
    };
#define POLYFORM_RUBIKS_H
#endif