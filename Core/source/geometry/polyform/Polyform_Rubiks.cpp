#include "geometry/GL4_Entity.hpp"
#include "geometry/GL4_PolyFunc.hpp"
#include "geometry/polyform/Polyform_Box.hpp"
#include "geometry/polyform/Polyform_Rubiks.hpp"

namespace Polyform_Rubiks_Eq {
    unsigned int xNum;
    float interval;
    float yOffset;
    float zOffset;

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

    float yEquation(float x){
        return yOffset;
    }

    float zEquation(float x, float y){
        return zOffset;
    }
}

void Polyform_Rubiks::createXI(GL4_PolyFunc* polyFunc, Polyform_Box* polyBox){
    Polyform_Box_Meta metaData;
    polyBox->exportMeta(&metaData);
    Polyform_Rubiks_Eq::xNum = Polyform_Rubiks::xCount;
    Polyform_Rubiks_Eq::interval = metaData.length;
    polyFunc->xSequence = Polyform_Rubiks_Eq::xSequence;
    polyFunc->gen_x();
    float yInc = metaData.width;
    // Polyform_Rubiks_Eq::yOffset = -1 * yInc * (float)Polyform_Rubiks::yCount / 2;
    Polyform_Rubiks_Eq::yOffset = -1 * yInc * (float)Polyform_Rubiks::yCount / 2 - yInc / 2;
    polyFunc->yEquation = Polyform_Rubiks_Eq::yEquation;
    for(unsigned int yElem = 0; yElem < Polyform_Rubiks::yCount; yElem++){
        Polyform_Rubiks_Eq::yOffset += yInc;
        polyFunc->gen_y();
    }
    float zInc = metaData.height;
    Polyform_Rubiks_Eq::zOffset = -1 * zInc * (float)Polyform_Rubiks::zCount / 2 - zInc / 2;
    polyFunc->zEquation = Polyform_Rubiks_Eq::zEquation;
    for(unsigned int zElem = 0; zElem < Polyform_Rubiks::zCount; zElem++){
        Polyform_Rubiks_Eq::zOffset += zInc;
        polyFunc->gen_z();
    }
    polyFunc->createXI();
}

void Polyform_Rubiks::create(GL4_PolyFunc* polyFunc, Polyform_Box* polyBox){
    Polyform_Box_Meta metaData;
    polyBox->exportMeta(&metaData);
    Polyform_Rubiks_Eq::xNum = Polyform_Rubiks::xCount;
    Polyform_Rubiks_Eq::interval = metaData.length;
    polyFunc->xSequence = Polyform_Rubiks_Eq::xSequence;
    polyFunc->gen_x();
    float yInc = metaData.width;
    // Polyform_Rubiks_Eq::yOffset = -1 * yInc * (float)Polyform_Rubiks::yCount / 2;
    Polyform_Rubiks_Eq::yOffset = -1 * yInc * (float)Polyform_Rubiks::yCount / 2 - yInc / 2;
    polyFunc->yEquation = Polyform_Rubiks_Eq::yEquation;
    for(unsigned int yElem = 0; yElem < Polyform_Rubiks::yCount; yElem++){
        Polyform_Rubiks_Eq::yOffset += yInc;
        polyFunc->gen_y();
    }
    float zInc = metaData.height;
    Polyform_Rubiks_Eq::zOffset = -1 * zInc * (float)Polyform_Rubiks::zCount / 2 - zInc / 2;
    polyFunc->zEquation = Polyform_Rubiks_Eq::zEquation;
    for(unsigned int zElem = 0; zElem < Polyform_Rubiks::zCount; zElem++){
        Polyform_Rubiks_Eq::zOffset += zInc;
        polyFunc->gen_z();
    }
    polyFunc->create();
}

void Polyform_Rubiks::exportMeta(Polyform_Rubiks_Meta* metaData){
    metaData->xCount = Polyform_Rubiks::xCount;
    metaData->yCount = Polyform_Rubiks::yCount;
    metaData->zCount = Polyform_Rubiks::zCount;
}