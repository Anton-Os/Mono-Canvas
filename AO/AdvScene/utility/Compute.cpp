#include "Utility.h"

float vertexProx = 0.1f;

void compFourProx(std::array<float, 12>* fourProx, const glm::vec2* pos, const std::vector<float>* posAccum){
	if(posAccum->size() < 4 || posAccum->empty()) {
		std::cerr << "posAccum was incorrectly formatted" << std::endl;
		return;
	}

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
        if(distLow <= vertexProx) return;
    }
}

void compFourProxAbs(std::array<float, 12>* fourProxAbs, const glm::vec2* pos, const std::vector<float>* posAccum){
	if(posAccum->size() < 4 || posAccum->empty()) {
		std::cerr << "posAccum was incorrectly formatted" << std::endl;
		return;
	}

	std::vector<float> distAccum;
    distAccum.resize(posAccum->size() / 3);
    std::array<unsigned int, 4> fourProxIndices;
    std::array<float, 12> fourProx;
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
        fourProx[fourProxElem * 3] = posAccum->at(indexLow * 3);
		fourProx[fourProxElem * 3 + 1] = posAccum->at(indexLow * 3 + 1);
		fourProx[fourProxElem * 3 + 2] = posAccum->at(indexLow * 3 + 2);
        if(distLow <= vertexProx) return;
    }

    for(unsigned int fourProxElem = 0; fourProxElem < 4; fourProxElem++){
        // Here address the special case if the point lies on the line exactly or close
        if(fourProx[fourProxElem * 3] < pos->x && fourProx[fourProxElem * 3 + 1] < pos->y){
            fourProxAbs->at(0) = fourProx[fourProxElem * 3];
            fourProxAbs->at(1) = fourProx[fourProxElem * 3 + 1];
            fourProxAbs->at(2) = fourProx[fourProxElem * 3 + 2];
        } else if(fourProx[fourProxElem * 3] > pos->x && fourProx[fourProxElem * 3 + 1] < pos->y){
            fourProxAbs->at(3) = fourProx[fourProxElem * 3];
            fourProxAbs->at(4) = fourProx[fourProxElem * 3 + 1];
            fourProxAbs->at(5) = fourProx[fourProxElem * 3 + 2];
        } else if(fourProx[fourProxElem * 3] < pos->x && fourProx[fourProxElem * 3 + 1] > pos->y){
            fourProxAbs->at(6) = fourProx[fourProxElem * 3];
            fourProxAbs->at(7) = fourProx[fourProxElem * 3 + 1];
            fourProxAbs->at(8) = fourProx[fourProxElem * 3 + 2];
        } else if(fourProx[fourProxElem * 3] > pos->x && fourProx[fourProxElem * 3 + 1] > pos->y){
            fourProxAbs->at(9) = fourProx[fourProxElem * 3];
            fourProxAbs->at(10) = fourProx[fourProxElem * 3 + 1];
            fourProxAbs->at(11) = fourProx[fourProxElem * 3 + 2];
        }
    }
}

/* float compHeight(std::array<unsigned int, 4> fourClosest){
    return 0.0f;
} */

float compLocalZ(std::array<float, 12>* fourProx, const glm::vec2* pos){
    if(glm::distance(*pos, glm::vec2(fourProx->at(0), fourProx->at(1))) < vertexProx)
        return fourProx->at(2);
    else return 0.0f;
}