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