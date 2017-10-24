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

MidPointTrig Scene_PlaneCollision::proxMidPoint(const MidPoint45* midPoint, const glm::vec2* posXY){
    MidPointTrig midPointT;
    if(glm::distance(glm::vec2(midPoint->t1[0], midPoint->t1[1]), *posXY) < glm::distance(glm::vec2(midPoint->t2[0], midPoint->t2[1]), *posXY)){
        midPointT.pos[0] = midPoint->t1[0];
        midPointT.pos[1] = midPoint->t1[1];
        midPointT.pos[2] = midPoint->t1[2];

        midPointT.threeProx[0] = midPoint->fourProx[midPoint->threeIndex1[0] * 3];
        midPointT.threeProx[1] = midPoint->fourProx[midPoint->threeIndex1[0] * 3 + 1];
        midPointT.threeProx[2] = midPoint->fourProx[midPoint->threeIndex1[0] * 3 + 2];
        midPointT.threeProx[3] = midPoint->fourProx[midPoint->threeIndex1[1] * 3];
        midPointT.threeProx[4] = midPoint->fourProx[midPoint->threeIndex1[1] * 3 + 1];
        midPointT.threeProx[5] = midPoint->fourProx[midPoint->threeIndex1[1] * 3 + 2];
        midPointT.threeProx[6] = midPoint->fourProx[midPoint->threeIndex1[2] * 3];
        midPointT.threeProx[7] = midPoint->fourProx[midPoint->threeIndex1[2] * 3 + 1];
        midPointT.threeProx[8] = midPoint->fourProx[midPoint->threeIndex1[2] * 3 + 2];
    } else {
        midPointT.pos[0] = midPoint->t2[0];
        midPointT.pos[1] = midPoint->t2[1];
        midPointT.pos[2] = midPoint->t2[2];

        midPointT.threeProx[0] = midPoint->fourProx[midPoint->threeIndex2[0] * 3];
        midPointT.threeProx[1] = midPoint->fourProx[midPoint->threeIndex2[0] * 3 + 1];
        midPointT.threeProx[2] = midPoint->fourProx[midPoint->threeIndex2[0] * 3 + 2];
        midPointT.threeProx[3] = midPoint->fourProx[midPoint->threeIndex2[1] * 3];
        midPointT.threeProx[4] = midPoint->fourProx[midPoint->threeIndex2[1] * 3 + 1];
        midPointT.threeProx[5] = midPoint->fourProx[midPoint->threeIndex2[1] * 3 + 2];
        midPointT.threeProx[6] = midPoint->fourProx[midPoint->threeIndex2[2] * 3];
        midPointT.threeProx[7] = midPoint->fourProx[midPoint->threeIndex2[2] * 3 + 1];
        midPointT.threeProx[8] = midPoint->fourProx[midPoint->threeIndex2[2] * 3 + 2];
    }
    return midPointT;
}

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

MidPoint45 Scene_PlaneCollision::proxMidPoint(const std::vector<MidPoint45>* midPoints, const glm::vec2* posXY){
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