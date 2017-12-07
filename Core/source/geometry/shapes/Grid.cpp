#include "geometry/GL4_PolyFunc.hpp"
#include "geometry/shapes/Grid.hpp"

namespace Grid_Eq {
    float yOffset;
    float zOffset;
    unsigned int xNum;
    float interval;

    void xFunc(std::vector<float>* xVals){
        xVals->resize(xNum);
        float xMiddle = interval / 2.0f;
        short int indexOffset = -1;
        unsigned int repCount = xNum;
        if(repCount % 2 == 1){
            xVals->at(repCount / 2) = 0.0f;
            xMiddle = 0.0f;
            indexOffset = 0;
            repCount--;
        }
        for(unsigned int xElem = repCount / 2; xElem > 0; xElem--){
            xVals->at(repCount / 2 - xElem) = -1.0f * interval * xElem + xMiddle;
            xVals->at(repCount / 2 + (xElem + indexOffset)) = interval * xElem - xMiddle;
        }
        
        std::sort(xVals->begin(), xVals->end());
    }

    /* float yFunc(float x){
        float* yOffsetPtr = &yOffset;
        return *yOffsetPtr;
    }

    float zFunc(float x, float y){
        float* zOffsetPtr = &zOffset;
        return *zOffsetPtr;
    } */
    float yFunc(float x){ return yOffset; }

    float zFunc(float x, float y){ return zOffset; }

}

void Grid::create(GL4_PolyFunc* polyFunc){
    Grid_Eq::xNum = Grid::xCount;
    Grid_Eq::interval = Grid::width / (float)Grid::xCount;
    polyFunc->xEquation = Grid_Eq::xFunc;
    polyFunc->gen_x();
    float yInc = Grid::height / (float)Grid::yCount;
    Grid_Eq::yOffset = -1 * Grid::height / 2.0f;
    polyFunc->yEquation = Grid_Eq::yFunc;
    for(unsigned int yElem = 0; yElem < Grid::yCount; yElem++){
        polyFunc->gen_y();
        Grid_Eq::yOffset += yInc;
    }
    polyFunc->zEquation = Grid_Eq::zFunc;
    Grid_Eq::zOffset = -0.2f;
    polyFunc->gen_z();
    Grid_Eq::zOffset = -0.1f;
    polyFunc->gen_z();
    Grid_Eq::zOffset = 0.0f;
    polyFunc->gen_z();
    Grid_Eq::zOffset = 0.1f;
    polyFunc->gen_z();
    Grid_Eq::zOffset = 0.2f;
    polyFunc->gen_z();
    polyFunc->create();
}
