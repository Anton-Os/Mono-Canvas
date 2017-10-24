#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cfloat>
#include <limits>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Geometry.h"

class Scene_PlaneCollision {
public:
    MidPointTrig proxMidPoint(const std::vector<MidPointTrig>* midPoints, const glm::vec2* posXY);
    MidPointTrig proxMidPoint(const MidPoint45* midPoint, const glm::vec2* posXY);
    MidPointQuad proxMidPoint(const std::vector<MidPointQuad>* midPoints, const glm::vec2* posXY);
    MidPoint45 proxMidPoint(const std::vector<MidPoint45>* midPoints, const glm::vec2* posXY);
    void calcZ(MidPointTrig* midPoint, const glm::vec2* posXY);
    glm::vec3 calcV90(MidPointTrig* midPoint);
};