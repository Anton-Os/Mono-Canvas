#include "geometry/GL4_PolyFunc.hpp"
#include "geometry/CartesianGrid.hpp"

namespace CartesianGrid_Eq {
    float yOffset;
    float rise;
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

    float zFunc(float x, float y){
        float* risePtr = &rise;
        return *risePtr;
    }
}

void CartesianGrid::create(GL4_PolyFunc* polyFunc){
    CartesianGrid_Eq::xNum = CartesianGrid::xCount;
    CartesianGrid_Eq::interval = CartesianGrid::width / (float)CartesianGrid::xCount;
    polyFunc->xEquation = CartesianGrid_Eq::xFunc;
    polyFunc->gen_x();
    float yInc = CartesianGrid::height / (float)CartesianGrid::yCount;
    CartesianGrid_Eq::yOffset = -1 * CartesianGrid::height / 2.0f;
    polyFunc->yEquation = CartesianGrid_Eq::yFunc;
    for(unsigned int yElem = 0; yElem < CartesianGrid::yCount; yElem++){
        polyFunc->gen_y();
        CartesianGrid_Eq::yOffset += yInc;
    }
    polyFunc->zEquation = CartesianGrid_Eq::zFunc;
    CartesianGrid_Eq::rise = 0.2f;
    polyFunc->gen_z();
    CartesianGrid_Eq::rise = -0.2f;
    polyFunc->gen_z();
    polyFunc->create();
    return;
}
