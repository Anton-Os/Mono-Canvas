#include "Scene.h"

/* void Scene_PlaneCollision::calc_middle(const std::vector<float>* posAccum, const std::vector<unsigned int>* indexAccum){
    for(unsigned int indexSet = 0; indexSet < indexAccum->size() / 6; indexSet++){
		std::array<unsigned int, 4> noDuplicates = {posAccum->size() + 1, posAccum->size() + 1, posAccum->size() + 1, posAccum->size() + 1};
        unsigned int indexStride = indexSet * 6;
        unsigned int indexDupl = 0;
        for(unsigned int indexElem = 0; indexDupl < 4; indexElem++){
            if(indexAccum->at(indexStride + indexElem) != noDuplicates[0] && indexAccum->at(indexStride + indexElem) != noDuplicates[1] && indexAccum->at(indexStride + indexElem) != noDuplicates[2]){
                noDuplicates[indexDupl] = indexAccum->at(indexStride + indexElem);
                indexDupl++;
            }
        }
        float avrgX = (posAccum->at(noDuplicates[0] * 3) + posAccum->at(noDuplicates[1] * 3) + posAccum->at(noDuplicates[2] * 3) + posAccum->at(noDuplicates[3] * 3)) / 4;
        float avrgY = (posAccum->at(noDuplicates[0] * 3 + 1) + posAccum->at(noDuplicates[1] * 3 + 1) + posAccum->at(noDuplicates[2] * 3 + 1) + posAccum->at(noDuplicates[3] * 3 + 1)) / 4;
        float avrgZ = (posAccum->at(noDuplicates[0] * 3 + 2) + posAccum->at(noDuplicates[1] * 3 + 2) + posAccum->at(noDuplicates[2] * 3 + 2) + posAccum->at(noDuplicates[3] * 3 + 2)) / 4;
        Scene_PlaneCollision::middleAccum.push_back(avrgX);
        Scene_PlaneCollision::middleAccum.push_back(avrgY);
        Scene_PlaneCollision::middleAccum.push_back(avrgZ);
    }
} */