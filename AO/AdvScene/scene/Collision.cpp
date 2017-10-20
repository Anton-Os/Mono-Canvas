#include "Scene.h"

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

void compFourProx(std::array<float, 12>* fourProxPos, std::array<float, 4>* fourProxDist, const glm::vec2* pos, const std::vector<float>* posAccum){
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
        fourProxDist->at(fourProxElem) = distLow;
        fourProxPos->at(fourProxElem * 3) = posAccum->at(indexLow * 3);
		fourProxPos->at(fourProxElem * 3 + 1) = posAccum->at(indexLow * 3 + 1);
		fourProxPos->at(fourProxElem * 3 + 2) = posAccum->at(indexLow * 3 + 2);
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

float compLocalZ(std::array<float, 12>* fourProx, const glm::vec2* pos){
    if(glm::distance(*pos, glm::vec2(fourProx->at(0), fourProx->at(1))) < vertexProx)
        return fourProx->at(2);
    else return 0.0f;
}

float compLocalZ(std::array<float, 12>* fourProxPos, std::array<float, 4>* fourProxDist){
    if(fourProxDist->at(0) < vertexProx) return fourProxPos->at(2);

    float distLength = std::sqrt(std::pow(fourProxDist->at(0), 2) + std::pow(fourProxDist->at(1), 2) + std::pow(fourProxDist->at(2), 2) + std::pow(fourProxDist->at(3), 2));
    std::array<float, 4> distNrmZ = {fourProxDist->at(0) / distLength, fourProxDist->at(1) / distLength, fourProxDist->at(2) / distLength, fourProxDist->at(3) / distLength};
    distNrmZ = {distNrmZ[0] * fourProxPos->at(2), distNrmZ[1] * fourProxPos->at(5), distNrmZ[2] * fourProxPos->at(8), distNrmZ[3] * fourProxPos->at(11)};
    return (distNrmZ[0] + distNrmZ[1] + distNrmZ[2] + distNrmZ[3]) / 4.0f;
}