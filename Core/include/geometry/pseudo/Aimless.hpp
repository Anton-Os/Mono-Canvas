#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef ENTITY_H
    #include "geometry/GL4_Entity.hpp"
#endif

#ifndef AIMLESS_H
    class Aimless {
    public:
        Aimless(){
            create();
        }
        void create();
    };
    #define AIMLESS_H
#endif