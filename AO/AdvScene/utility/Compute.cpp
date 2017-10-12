#include "Utility.h"

/* std::array<unsigned int, 4> compFourClosest(glm::vec2* pos, std::vector<float>* posAccum){
    std::array<unsigned int, 4> fourClosest;
    GLuint fourClosestElem = 0;
    for(GLuint posElem = 0; posElem < posAccum->size(); posElem++){
        if(pos->x > posAccum->at(fourClosest[fourClosestElem % 4] * 3) && pos->y > posAccum->at(fourClosest[fourClosestElem % 4] * 3 + 1)){
            fourClosestElem++;
            fourClosest[fourClosestElem % 4] = posElem;
        }
    }
    return fourClosest;
} */

void compFourProx(std::array<float, 12>* fourProx, const glm::vec2* pos, const std::vector<float>* posAccum){
    GLuint fourProxElem = 0;
    for(GLuint posElem = 0; posElem < posAccum->size() / 3; posElem++){
        // if(posAccum->at(posElem * 3) > fourProx->at((fourProxElem % 4) * 3) && posAccum->at(posElem * 3 + 1) > fourProx->at((fourProxElem % 4) * 3 + 1)){
        float distanceNext = glm::distance(*pos, glm::vec2(posAccum->at(posElem * 3), posAccum->at(posElem * 3 + 1)));
        float distancePrev = glm::distance(*pos, glm::vec2(fourProx->at((fourProxElem % 4) * 3), posAccum->at(posElem * 3 + 1)));
        if(distanceNext > distancePrev){
            fourProxElem++;
            fourProx->at((fourProxElem % 4) * 3) = posAccum->at(posElem * 3);
            fourProx->at((fourProxElem % 4) * 3 + 1) = posAccum->at(posElem * 3 + 1);
            fourProx->at((fourProxElem % 4) * 3 + 2) = posAccum->at(posElem * 3 + 2);
        }
    }
}

/* float compHeight(std::array<unsigned int, 4> fourClosest){
    return 0.0f;
} */

float compLocalZ(std::array<float, 12>* fourProx, const glm::vec2* pos){
    return 0.0f;
}