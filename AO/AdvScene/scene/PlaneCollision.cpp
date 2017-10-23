#include "Scene.h"

MidPointTrig Scene_PlaneCollision::proxMidPoint(const std::vector<MidPointTrig>* midPoints, const glm::vec2* posXY){
    GLuint midPointIndex = 0;
    float minDistance = FLT_MAX;
    for(GLuint midPointElem = 0; midPointElem < midPoints->size(); midPointElem++){
        glm::vec2 midPointXY = glm::vec2(midPoints->at(midPointElem).pos[0], midPoints->at(midPointElem).pos[1]);
        if(glm::distance(midPointXY, *posXY) < minDistance){
            minDistance = glm::distance(midPointXY, *posXY);
            midPointIndex = midPointElem;
        }
    }
    return midPoints->at(midPointIndex);
}

/* MidPointTrig Scene_PlaneCollision::proxMidPointT(const std::vector<MidPointQuad>* midPoints, const glm::vec2* posXY){
    GLuint midPointIndex = 0;
    float minDistance = FLT_MAX;
    for(GLuint midPointElem = 0; midPointElem < midPoints->size(); midPointElem++){
        glm::vec2 midPointXY = glm::vec2(midPoints->at(midPointElem).pos[0], midPoints->at(midPointElem).pos[1]);
        if(glm::distance(midPointXY, *posXY) < minDistance){
            minDistance = glm::distance(midPointXY, *posXY);
            midPointIndex = midPointElem;
        }
    }
    MidPointQuad midPointQ = midPoints->at(midPointIndex);
    glm::vec3 mpointT1(1);
    mpointT1.x = (midPointQ.fourProx[0] + midPointQ.fourProx[4] + midPointQ.fourProx[8]) / 3;
    mpointT1.y = (midPointQ.fourProx[1] + midPointQ.fourProx[5] + midPointQ.fourProx[9]) / 3;
    mpointT1.z = (midPointQ.fourProx[2] + midPointQ.fourProx[6] + midPointQ.fourProx[10]) / 3;
    glm::vec3 mpointT2(1);
    mpointT2.x = (midPointQ.fourProx[1] + midPointQ.fourProx[5] + midPointQ.fourProx[9]) / 3;
    mpointT2.y = (midPointQ.fourProx[2] + midPointQ.fourProx[6] + midPointQ.fourProx[10]) / 3;
    mpointT2.z = (midPointQ.fourProx[3] + midPointQ.fourProx[7] + midPointQ.fourProx[11]) / 3;
    MidPointTrig midPointT;
    if(glm::distance(midPointT1, *posXY) < glm::distance(midPointtT2, *posXY)){
        midPointT = { {mpointT1.x, mpointT1.y, mpointT1.z}, 
            { midPointQ.fourProx[0] + midPointQ.fourProx[4] + midPointQ.fourProx[8],
              midPointQ.fourProx[1] + midPointQ.fourProx[5] + midPointQ.fourProx[9],
              midPointQ.fourProx[2] + midPointQ.fourProx[6] + midPointQ.fourProx[10]
            }
        };
    } else {
        midPointT = { {mpointT2.x, mpointT2.y, mpointT2.z}, 
            { midPointQ.fourProx[1] + midPointQ.fourProx[5] + midPointQ.fourProx[9],
              midPointQ.fourProx[2] + midPointQ.fourProx[6] + midPointQ.fourProx[10],
              midPointQ.fourProx[3] + midPointQ.fourProx[7] + midPointQ.fourProx[11]
            }
        };
    }
    return midPointT;
} */

MidPointQuad Scene_PlaneCollision::proxMidPoint(const std::vector<MidPointQuad>* midPoints, const glm::vec2* posXY){
    GLuint midPointIndex = 0;
    float minDistance = FLT_MAX;
    for(GLuint midPointElem = 0; midPointElem < midPoints->size(); midPointElem++){
        glm::vec2 midPointXY = glm::vec2(midPoints->at(midPointElem).pos[0], midPoints->at(midPointElem).pos[1]);
        if(glm::distance(midPointXY, *posXY) < minDistance){
            minDistance = glm::distance(midPointXY, *posXY);
            midPointIndex = midPointElem;
        }
    }
    return midPoints->at(midPointIndex);
}