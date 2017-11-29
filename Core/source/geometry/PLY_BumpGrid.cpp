#include "geometry/GL4_PolyFunc.hpp"
#include "geometry/PLY_BumpGrid.hpp"

namespace BumpGrid_Eq {
    float height;
    float yOffset;
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

    float yFunc(float x){
        float* yOffsetPtr = &yOffset;
        return *yOffsetPtr;
    }

    float zNormal(float x, float y){
        return height;
    } 
}

void PLY_BumpGrid::create(GL4_PolyFunc* polyFunc){
    BumpGrid_Eq::xNum = PLY_BumpGrid::xCount;
    BumpGrid_Eq::interval = PLY_BumpGrid::width / (float)PLY_BumpGrid::xCount;
    polyFunc->xEquation = BumpGrid_Eq::xFunc;
    polyFunc->gen_x();
    float yInc = PLY_BumpGrid::height / (float)PLY_BumpGrid::yCount;
    BumpGrid_Eq::yOffset = -1 * PLY_BumpGrid::height / 2.0f;
    polyFunc->yEquation = BumpGrid_Eq::yFunc;
    for(unsigned int yElem = 0; yElem < PLY_BumpGrid::yCount; yElem++){
        polyFunc->gen_y();
        BumpGrid_Eq::yOffset += yInc;
    }
    BumpGrid_Eq::height = PLY_BumpGrid::rise;
    if(PLY_BumpGrid::zMode == normal) polyFunc->zEquation = BumpGrid_Eq::zNormal;
    polyFunc->gen_z();
    polyFunc->create();
    return;
}
