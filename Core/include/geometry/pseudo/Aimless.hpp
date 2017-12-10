#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef AIMLESS_H
    class Aimless {
    public:
        Aimless(GL4_PolyFunc* polyFunc){
            polyFunc->reset();
            create(polyFunc);
        }
        void create(GL4_PolyFunc* polyFunc);
    };
    #define AIMLESS_H
#endif