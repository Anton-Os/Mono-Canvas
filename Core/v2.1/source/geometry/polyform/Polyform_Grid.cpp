#include "geometry/polyform/Polyform_Grid.hpp"

namespace Polyform_Grid_Eq {
    float yOffset;
    float zOffset;
    unsigned int xNum;
    float interval;

    void xSequence(std::vector<float>* xVals){
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

    float yEquation(float x){ return yOffset; }

    float zEquation(float x, float y){ return zOffset; }
}

void Polyform_Grid::create(GL4_PolyFunc* polyFunc){
    Polyform_Grid_Eq::xNum = Polyform_Grid::xCount;
    Polyform_Grid_Eq::interval = Polyform_Grid::width / (float)Polyform_Grid::xCount;
    polyFunc->xSequence = Polyform_Grid_Eq::xSequence;
    polyFunc->gen_x();
    float yInc = Polyform_Grid::height / (float)Polyform_Grid::yCount;
    Polyform_Grid_Eq::yOffset = -1 * Polyform_Grid::height / 2.0f;
    polyFunc->yEquation = Polyform_Grid_Eq::yEquation;
    for(unsigned int yElem = 0; yElem < Polyform_Grid::yCount; yElem++){
        polyFunc->gen_y();
        Polyform_Grid_Eq::yOffset += yInc;
    }
    polyFunc->zEquation = Polyform_Grid_Eq::zEquation;
    Polyform_Grid_Eq::zOffset = 0.0f;
    polyFunc->gen_z();
}
