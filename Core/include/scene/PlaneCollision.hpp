#ifndef GEOMETRY_H
    #include "geometry/Geometry.hpp"
    #define GEOMETRY_H
#endif

#include <cfloat>

class Scene_PlaneCollision {
public:
    MidPointTrig proxMidPoint(const std::vector<MidPointTrig>* midPoints, const glm::vec2* posXY);
    MidPointTrig proxMidPoint(const MidPoint45* midPoint, const glm::vec2* posXY);
    MidPointQuad proxMidPoint(const std::vector<MidPointQuad>* midPoints, const glm::vec2* posXY);
    MidPoint45 proxMidPoint(const std::vector<MidPoint45>* midPoints, const glm::vec2* posXY);
    void waves(float rise, const std::vector<MidPointQuad>* midPoints, std::vector<float>* clampedVals);
    float calcZ(const MidPointTrig* midPoint, const glm::vec2* posXY);
    bool trigFlip(const MidPointTrig* midPoint, const glm::vec2* posXY);
    glm::vec3 calcV90(const MidPointTrig* midPoint);
};