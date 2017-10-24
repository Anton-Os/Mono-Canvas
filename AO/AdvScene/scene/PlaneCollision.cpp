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

glm::vec3 Scene_PlaneCollision::calcV90(const MidPointTrig* midPoint){
    float v1 = glm::distance(glm::vec2(midPoint->threeProx[0], midPoint->threeProx[1]), glm::vec2(midPoint->pos[0], midPoint->pos[1]));
    float v2 = glm::distance(glm::vec2(midPoint->threeProx[3], midPoint->threeProx[4]), glm::vec2(midPoint->pos[0], midPoint->pos[1]));    
    float v3 = glm::distance(glm::vec2(midPoint->threeProx[6], midPoint->threeProx[7]), glm::vec2(midPoint->pos[0], midPoint->pos[1]));
    unsigned int closeIndex;

    if(v1 < v2 && v1 < v3) closeIndex = 0;
    else if(v2 < v1 && v2 < v3) closeIndex = 1;
    else if(v3 < v1 && v3 < v2) closeIndex = 2;

    return glm::vec3(midPoint->threeProx[closeIndex * 3], midPoint->threeProx[closeIndex * 3 + 1], midPoint->threeProx[closeIndex * 3 + 2]);
}

float Scene_PlaneCollision::calcZ(const MidPointTrig* midPoint, const glm::vec2* posXY){
    float vDist[3];
    vDist[0] = glm::distance(glm::vec2(midPoint->threeProx[0], midPoint->threeProx[1]), glm::vec2(midPoint->pos[0], midPoint->pos[1]));
    vDist[1] = glm::distance(glm::vec2(midPoint->threeProx[3], midPoint->threeProx[4]), glm::vec2(midPoint->pos[0], midPoint->pos[1]));    
    vDist[2] = glm::distance(glm::vec2(midPoint->threeProx[6], midPoint->threeProx[7]), glm::vec2(midPoint->pos[0], midPoint->pos[1]));
    unsigned int closeIndex;
    unsigned int farIndices[2];

    if(vDist[0] < vDist[1] && vDist[0] < vDist[2]){
        closeIndex = 0;
        farIndices[0] = 1;
        farIndices[1] = 2;
    } 
    else if(vDist[1] < vDist[0] && vDist[1] < vDist[2]){
        closeIndex = 1;
        farIndices[0] = 0;
        farIndices[1] = 2;
    } 
    else if(vDist[2] < vDist[0] && vDist[2] < vDist[1]){
        closeIndex = 2;
        farIndices[0] = 0;
        farIndices[1] = 1;
    }

    if(midPoint->threeProx[closeIndex * 3] != midPoint->threeProx[farIndices[0]]){
        unsigned int switchIndex = farIndices[0];
        farIndices[0] = farIndices[1];
        farIndices[1] = switchIndex;
    }

    glm::vec2 closeVec(midPoint->threeProx[closeIndex * 3], midPoint->threeProx[closeIndex * 3 + 1]);
    float farZ1; float farX; float pX;
    float farZ2; float farY; float pY;
    /* if(closeVec.x > posXY->x && closeVec.y > posXY->y){
        farZ1 = std::sqrt(std::pow(midPoint->threeProx[closeIndex * 3 + 2] - midPoint->threeProx[farIndices[0] * 3 + 2], 2));
        farZ2 = std::sqrt(std::pow(midPoint->threeProx[closeIndex * 3 + 2] - midPoint->threeProx[farIndices[1] * 3 + 2], 2));
        farX = std::sqrt(std::pow(midPoint->threeProx[closeIndex * 3] - midPoint->threeProx[farIndices[0] * 3], 2));
        pX = midPoint->threeProx[closeIndex * 3 + 2] - ((farX - posXY->x) * farZ1);
        farY = std::sqrt(std::pow(midPoint->threeProx[closeIndex * 3 + 1] - midPoint->threeProx[farIndices[0] * 3 + 1], 2));
        pY = midPoint->threeProx[closeIndex * 3 + 2] - ((farY - posXY->y) * farZ2);
    } else {
        farZ1 = std::sqrt(std::pow(midPoint->threeProx[farIndices[0] * 3 + 1] - midPoint->threeProx[closeIndex * 3 + 1], 2));
        farZ2 = std::sqrt(std::pow(midPoint->threeProx[farIndices[1] * 3 + 2] - midPoint->threeProx[closeIndex * 3 + 2], 2));
        farX = std::sqrt(std::pow(midPoint->threeProx[farIndices[0] * 3] - midPoint->threeProx[closeIndex * 3], 2));
        pX = midPoint->threeProx[closeIndex * 3 + 2] + ((farX - posXY->x) * farZ1);
        farY = std::sqrt(std::pow(midPoint->threeProx[farIndices[0] * 3 + 1] - midPoint->threeProx[closeIndex * 3 + 1], 2));
        pY = midPoint->threeProx[closeIndex * 3 + 2] + ((farY - posXY->y) * farZ2);
    } */
    
    return 1.0;
}

bool Scene_PlaneCollision::trigFlip(const MidPointTrig* midPoint, const glm::vec2* posXY){
    float vDist[3];
    vDist[0] = glm::distance(glm::vec2(midPoint->threeProx[0], midPoint->threeProx[1]), glm::vec2(midPoint->pos[0], midPoint->pos[1]));
    vDist[1] = glm::distance(glm::vec2(midPoint->threeProx[3], midPoint->threeProx[4]), glm::vec2(midPoint->pos[0], midPoint->pos[1]));    
    vDist[2] = glm::distance(glm::vec2(midPoint->threeProx[6], midPoint->threeProx[7]), glm::vec2(midPoint->pos[0], midPoint->pos[1]));
    unsigned int closeIndex;
    unsigned int farIndices[2];

    if(vDist[0] < vDist[1] && vDist[0] < vDist[2]){
        closeIndex = 0;
        farIndices[0] = 1;
        farIndices[1] = 2;
    } 
    else if(vDist[1] < vDist[0] && vDist[1] < vDist[2]){
        closeIndex = 1;
        farIndices[0] = 0;
        farIndices[1] = 2;
    } 
    else if(vDist[2] < vDist[0] && vDist[2] < vDist[1]){
        closeIndex = 2;
        farIndices[0] = 0;
        farIndices[1] = 1;
    }

    if(midPoint->threeProx[closeIndex * 3] != midPoint->threeProx[farIndices[0]]){
        unsigned int switchIndex = farIndices[0];
        farIndices[0] = farIndices[1];
        farIndices[1] = switchIndex;
    }

    glm::vec2 closeVec(midPoint->threeProx[closeIndex * 3], midPoint->threeProx[closeIndex * 3 + 1]);
    float farZ1;
    float farZ2;
    if(closeVec.x > posXY->x && closeVec.y > posXY->y){
        farZ1 = midPoint->threeProx[closeIndex * 3 + 1] - midPoint->threeProx[farIndices[0] * 3 + 1];
        farZ2 = midPoint->threeProx[closeIndex * 3 + 2] - midPoint->threeProx[farIndices[1] * 3 + 2];
        return true;
    } else {
        farZ1 = midPoint->threeProx[farIndices[0] * 3 + 1] - midPoint->threeProx[closeIndex * 3 + 1];
        farZ2 = midPoint->threeProx[farIndices[1] * 3 + 2] - midPoint->threeProx[closeIndex * 3 + 2];
        return false;
    }
}