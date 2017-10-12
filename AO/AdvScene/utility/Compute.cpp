#include "Utility.h"

void compFourProx(std::array<float, 12>* fourProx, const glm::vec2* pos, const std::vector<float>* posAccum){
    std::vector<float> distAccum;
    distAccum.resize(posAccum->size() / 3);
    std::array<unsigned int, 4> fourProxIndices;
    for(GLuint distElem = 0; distElem < distAccum.size(); distElem++)
        distAccum[distElem] = glm::distance(*pos, glm::vec2(posAccum->at(distElem * 3), posAccum->at(distElem * 3 + 1)));
   
    for(unsigned int fourProxElem = 0; fourProxElem < 4; fourProxElem++){
        float distLow = FLT_MAX;
        unsigned int indexLow = 0;
        for(unsigned int distElem = 0; distElem < distAccum.size(); distElem++){
            if(distAccum[distElem] < distLow && distElem != fourProxIndices[0] && distElem != fourProxIndices[1] && distElem != fourProxIndices[2]){
                distLow = distAccum[distElem];
                indexLow = distElem;
            }
        }
        fourProxIndices[fourProxElem] = indexLow;
        fourProx->at(fourProxElem * 3) = posAccum->at(indexLow * 3);
		fourProx->at(fourProxElem * 3 + 1) = posAccum->at(indexLow * 3 + 1);
		fourProx->at(fourProxElem * 3 + 2) = posAccum->at(indexLow * 3 + 2);

    } 

	// for(unsigned int fourProxElem = 0; fourProxElem < 
}

/* float compHeight(std::array<unsigned int, 4> fourClosest){
    return 0.0f;
} */

float compLocalZ(std::array<float, 12>* fourProx, const glm::vec2* pos){
    return 0.0f;
}