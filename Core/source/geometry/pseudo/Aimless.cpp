#include "geometry/GL4_PolyFunc.hpp"
#include "geometry/pseudo/Aimless.hpp"

namespace Aimless_Eq {
    unsigned int vCount = 40;
    float length = 2.5f;

    void xSequence(std::vector<float>* xVals){
        float xInc = 1.0f / 40;
        float xOffset = -1.0f * length / 2.0f;
        while(xOffset <= length / 2){
            xVals->push_back(xOffset);
            xOffset += xInc;
        }
    }

    float yEquation(float x){
        return 0.0f;
    }

    float zEquation(float x, float y){
        return 0.0f;
    }
}

void Aimless::create(GL4_PolyFunc* polyFunc){
    polyFunc->xSequence = Aimless_Eq::xSequence;
    polyFunc->gen_x();
    polyFunc->yEquation = Aimless_Eq::yEquation;
    polyFunc->gen_y();
    polyFunc->zEquation = Aimless_Eq::zEquation;
    polyFunc->gen_z();
    polyFunc->createXI();
}