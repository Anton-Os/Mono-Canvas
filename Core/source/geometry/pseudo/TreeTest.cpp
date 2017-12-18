#include "geometry/pseudo/TreeTest.hpp"

namespace TreeTest_Eq {
    unsigned mtxNum;
    float interval;

    void mtxSequence(std::vector<glm::mat4>* matrices){
        std::vector<float> xVals;
        xVals.resize(mtxNum);
        float xMiddle = interval / 2.0f;
        short int indexOffset = -1;
        unsigned int repCount = mtxNum;
        if(repCount % 2 == 1){
            xVals.at(repCount / 2) = 0.0f;
            xMiddle = 0.0f;
            indexOffset = 0;
            repCount--;
        }
        for(unsigned int xElem = repCount / 2; xElem > 0; xElem--){
            xVals.at(repCount / 2 - xElem) = -1.0f * interval * xElem + xMiddle;
            xVals.at(repCount / 2 + (xElem + indexOffset)) = interval * xElem - xMiddle;
        }
        
        std::sort(xVals.begin(), xVals.end());

        for(unsigned xElem = 0; xElem < mtxNum; xElem++)
            matrices->push_back(glm::translate(glm::mat4(1), glm::vec3(xVals[xElem])));
    }
};

void TreeTest::createXI(GL4_PolyClone* polyClone){
    TreeTest_Eq::mtxNum = 9;
    TreeTest_Eq::interval = 0.5f;
    polyClone->mtxSequence = TreeTest_Eq::mtxSequence;
    polyClone->gen_mtx();
}
