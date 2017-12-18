#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef PATHFINDER_H
    class Pathfinder {
    public:
        Pathfinder(){
            polyFunc->exportMeta(&polyFuncMeta);
        }
        void gen_points(float thresh);
    private:
        GL4_PolyFunc_Meta polyFuncMeta;
    };
#endif