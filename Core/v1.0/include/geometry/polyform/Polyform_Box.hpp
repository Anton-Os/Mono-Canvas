#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLY_FUNC_H
    #include "geometry/polybase/GL4_PolyFunc.hpp"
#endif

#ifndef POLYFORM_BOX_H
    struct Polyform_Box_Meta {
        float length;
        float width;
        float height;
    };

    class Polyform_Box {
    public:
        Polyform_Box(float lengthArg, float widthArg, float heightArg){
            length = lengthArg;
            width = widthArg;
            height = heightArg;
        }
        Polyform_Box(GL4_PolyFunc* polyFunc, float lengthArg, float widthArg, float heightArg){
            length = lengthArg;
            width = widthArg;
            height = heightArg;
            polyFunc->reset();
            create(polyFunc);
        }
        void create(GL4_PolyFunc* polyFunc);
        void exportMeta(Polyform_Box_Meta* metaData);
    private:
        float length;
        float width;
        float height;
    };
#define POLYFORM_BOX_H
#endif