#include "Geometry.h"

void GL4_PolyFunc::gen_x(std::vector<float>* xVals, float interval, unsigned int reps){
    xVals->resize(reps);
    float offsetX = interval / 2.0f;
    short int indexOffset = -1;
    unsigned int repCount = reps;
    if(repCount % 2 == 1){
        xVals->at(repCount / 2) = 0.0f;
        offsetX = 0.0f;
        indexOffset = 0;
        repCount--;
    }
    for(unsigned int xElem = repCount / 2; xElem > 0; xElem--){
        xVals->at(repCount / 2 - xElem) = -1.0f * interval * xElem + offsetX;
        xVals->at(repCount / 2 + (xElem + indexOffset)) = interval * xElem - offsetX;
    }
}

void GL4_PolyFunc::gen_x(float interval, unsigned int reps){
    GL4_PolyFunc::xVals.resize(reps);
    float offsetX = interval / 2.0f;
    short int indexOffset = -1;
    unsigned int repCount = reps;
    if(repCount % 2 == 1){
        GL4_PolyFunc::xVals[repCount / 2] = 0.0f;
        offsetX = 0.0f;
        indexOffset = 0;
        repCount--;
    }
    for(unsigned int xElem = repCount / 2; xElem > 0; xElem--){
        GL4_PolyFunc::xVals[repCount / 2 - xElem] = -1.0f * interval * xElem + offsetX;
        GL4_PolyFunc::xVals[repCount / 2 + (xElem + indexOffset)] = interval * xElem - offsetX;
    }
}
