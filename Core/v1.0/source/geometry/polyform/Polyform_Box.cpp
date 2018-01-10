#include "geometry/polyform/Polyform_Box.hpp"

namespace Polyform_Box_Eq {
    float length;
    float width;
    float height;

    void xSequence(std::vector<float>* xVals){
        xVals->push_back(-1.0f * length / 2.0f);
        xVals->push_back(length / 2.0f);
    }

    /* void xSequence(std::vector<float>* xVals){
        float xInc = length / 40;
        float xOffset = -1.0f * length / 2.0f;
        while(xOffset <= length / 2){
            xVals->push_back(xOffset);
            xOffset += xInc;
        }
    } */

    float yEquation(float x){
        return width / 2.0f;
    }

    float zEquation(float x, float y){
        return height / 2.0f;
    }
}

void Polyform_Box::create(GL4_PolyFunc* polyFunc){
    Polyform_Box_Eq::length = Polyform_Box::length;
    polyFunc->xSequence = Polyform_Box_Eq::xSequence;
    polyFunc->gen_x();
    Polyform_Box_Eq::width = -1 * Polyform_Box::width;
    polyFunc->yEquation = Polyform_Box_Eq::yEquation;
    polyFunc->gen_y();
    Polyform_Box_Eq::width = Polyform_Box::width;
    polyFunc->gen_y();
    polyFunc->zEquation = Polyform_Box_Eq::zEquation;
    Polyform_Box_Eq::height = -1 * Polyform_Box::height;
    polyFunc->zEquation = Polyform_Box_Eq::zEquation;
    polyFunc->gen_z();
    Polyform_Box_Eq::height = Polyform_Box::height;
    polyFunc->gen_z();
    polyFunc->create();
}

void Polyform_Box::exportMeta(Polyform_Box_Meta* metaData){
    metaData->length = Polyform_Box::length;
    metaData->width = Polyform_Box::width;
    metaData->height = Polyform_Box::height;
}