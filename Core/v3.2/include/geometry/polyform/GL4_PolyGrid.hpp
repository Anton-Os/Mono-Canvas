#define PIPELINE_X
#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef POLY_FUNC_H
    #include "geometry/polybase/GL4_PolyFunc.hpp"
#endif

#ifndef POLYFORM_GRID_H
    class Polyform_Grid {
    public:
        Polyform_Grid(float w, unsigned x, float h, unsigned y) {
            width = w;
            xCount = x;
            height = h;
            yCount = y;
        }
        Polyform_Grid(GL4_PolyFunc* polyFunc, float w, unsigned x, float h, unsigned y) {
            width = w;
            xCount = x;
            height = h;
            yCount = y;
            polyFunc->reset();
            create(polyFunc);
        }
        void create(GL4_PolyFunc* polyFunc);
        void get_params(std::array<float, 2> dimensions);
        
    private:
        float width;
        unsigned int xCount;
        float height;
        unsigned int yCount;
    };
#define POLYFORM_GRID_H
#endif
