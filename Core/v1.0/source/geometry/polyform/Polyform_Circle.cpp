#include "geometry/polyform/Polyform_Circle.hpp"

namespace Polyform_Circle_Eq {
    unsigned int interval;
    float radius;
    // float angleInc = glm::pi<float>() * 2 / (float)Polyform_Circle::interval;

    void anglSequence(std::vector<float>* anglVals){
        anglVals->resize(interval + 1);
        float angleInc = glm::pi<float>() * 2 / (float)interval;
        for(unsigned int angleElem = 0; angleElem < interval + 1; angleElem++)
            anglVals->at(angleElem) = angleElem * angleInc;
    }

    float xEquation(float angle){ return std::sin(angle) * radius; }

    float yEquation(float angle){ return std::cos(angle) * radius; }

    float zEquation(float angle){ return 0.0; }
}

void Polyform_Circle::create(GL4_PolyAngles* polyAngles){
    Polyform_Circle_Eq::interval = Polyform_Circle::interval;
    Polyform_Circle_Eq::radius = Polyform_Circle::radius;
    polyAngles->anglSequence = Polyform_Circle_Eq::anglSequence;
    polyAngles->gen_angl();
    polyAngles->xEquation = Polyform_Circle_Eq::xEquation;
    polyAngles->gen_x();
    polyAngles->yEquation = Polyform_Circle_Eq::yEquation;
    polyAngles->gen_y();
    polyAngles->zEquation = Polyform_Circle_Eq::zEquation;
    polyAngles->gen_z();
    polyAngles->create();
}
