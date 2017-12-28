#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLY_FUNC_H
    #include "geometry/polybase/GL4_PolyFunc.hpp"
#endif

#ifndef POLY_CLONE_H
    #include "geometry/polybase/GL4_PolyClone.hpp"
#endif

#ifndef POLYFORM_GRID_H
    #include "geometry/polyform/Polyform_Grid.hpp"
#endif

#ifndef POLYFORM_TILEMAP_H
    struct Polyform_Tilemap_Picker {
        int defaultState = 0;
        unsigned perState = 1;
        std::vector<float> weights;
        std::vector<int> states;
    };

    class Polyform_Tilemap {
    public:
        Polyform_Tilemap(GL4_PolyClone* polyClone, Polyform_Grid* polyGrid){
            create(polyClone, polyGrid);
        }
    private:
        void create(GL4_PolyClone* polyClone, Polyform_Grid* polyGrid);
        std::vector<GLint> states;    
    };
#endif