#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLY_FUNC_H
    #include "geometry/GL4_PolyFunc.hpp"
#endif

#ifndef POLYFORM_GRID_H
    #include "geometry/polyform/Polyform_Grid.hpp"
#endif

#ifndef CELLULAR_H
    struct Cellular_Picker {
        int defaultState = 0;
        std::vector<float> weights;
        std::vector<int> states;
    };

    class Cellular {
    public:
        Cellular(GL4_PolyFunc* polyFunc, Polyform_Grid* polyGrid){
            polyFunc->reset();
            polyGrid->create(polyFunc);
            polyGrid->exportMeta(&polyGridMeta);
            states.resize(polyGridMeta.xCount * polyGridMeta.yCount);
        }
        void gen_points(float thresh);
        void gen_points(Cellular_Picker* cellPicker);
    private:
        Polyform_Grid_Meta polyGridMeta;
        std::vector<int> states;
    };
#endif