#include "geometry/GL4_PolyFunc.hpp"
#include "geometry/CartesianGrid.hpp"

/* void CartesianGrid_Eq::xEquation(std::vector<float>* xVals){
    xVals->resize(Math::xNum);
    float offsetX = Math::interval / 2.0f;
    short int indexOffset = -1;
    unsigned int repCount = Math::xNum;
    if(repCount % 2 == 1){
        xVals->at(repCount / 2) = 0.0f;
        offsetX = 0.0f;
        indexOffset = 0;
        repCount--;
    }
    for(unsigned int xElem = repCount / 2; xElem > 0; xElem--){
        xVals->at(repCount / 2 - xElem) = -1.0f * Math::interval * xElem + offsetX;
        xVals->at(repCount / 2 + (xElem + indexOffset)) = Math::interval * xElem - offsetX;
	}
	
	std::sort(xVals->begin(), xVals->end());
} */

/* void CartesianGrid::xEquation(std::vector<float>* xVals){
    return;
}

float CartesianGrid::yEquation(float x){
    return CartesianGrid::yOffset;
}

float CartesianGrid::zEquation(float x, float y){
    return 0.0;
} */

namespace CartesianGrid_Eq {
    float yOffset;
    unsigned int xNum;
    float interval;

    void xEquation(std::vector<float>* xVals){
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

    float yEquation(float x){
        float* yOffsetPtr = &yOffset;
        return *yOffsetPtr;
    }

    float zEquation(float x, float y){
        return 0.0;
    } 
}

void CartesianGrid::create(GL4_PolyFunc* polyFunc){
    CartesianGrid_Eq::xNum = CartesianGrid::xCount;
    CartesianGrid_Eq::interval = CartesianGrid::width / (float)CartesianGrid::xCount;
    polyFunc->xEquation = CartesianGrid_Eq::xEquation;
    polyFunc->gen_x();
    float yInc = CartesianGrid::height / (float)CartesianGrid::yCount;
    CartesianGrid_Eq::yOffset = -1 * CartesianGrid::height / 2.0f;
    polyFunc->yEquation = CartesianGrid_Eq::yEquation;
    for(unsigned int yElem = 0; yElem < CartesianGrid::yCount; yElem++){
        polyFunc->gen_y();
        CartesianGrid_Eq::yOffset += yInc;
    }
    polyFunc->zEquation = CartesianGrid_Eq::zEquation;
    polyFunc->gen_z();
    polyFunc->create();
    return;
}
