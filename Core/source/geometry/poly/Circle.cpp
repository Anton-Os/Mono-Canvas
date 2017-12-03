#include "geometry/GL4_PolyAngles.hpp"
#include "geometry/poly/Circle.hpp"

namespace Circle_Eq {
    unsigned int interval;
    float radius;
    // float angleInc = glm::pi<float>() * 2 / (float)Circle::interval;

    void anglFunc(std::vector<float>* anglVals){
        anglVals->resize(interval);
        float angleInc = glm::pi<float>() * 2 / (float)interval;
        for(unsigned int angleElem = 0; angleElem < interval; angleElem++)
            anglVals->at(angleElem) = angleElem * angleInc;
    }

    float xFunc(float angle){ return std::sin(angle) * radius; }

    float yFunc(float angle){ return std::cos(angle) * radius; }

    float zFunc(float angle){ return 0.0; }
}

void Circle::create(GL4_PolyAngles* polyAngles){
    Circle_Eq::interval = Circle::interval;
    Circle_Eq::radius = Circle::radius;
    polyAngles->anglEquation = Circle_Eq::anglFunc;
    polyAngles->gen_angl();
    polyAngles->xEquation = Circle_Eq::xFunc;
    polyAngles->gen_x();
    polyAngles->yEquation = Circle_Eq::yFunc;
    polyAngles->gen_y();
    polyAngles->zEquation = Circle_Eq::zFunc;
    polyAngles->gen_z();
    polyAngles->createXI();
}
