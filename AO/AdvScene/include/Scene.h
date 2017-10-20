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
};

void compFourProx(std::array<float, 12>* fourProx, const glm::vec2* pos, const std::vector<float>* posAccum);
void compFourProx(std::array<float, 12>* fourProxPos, std::array<float, 4>* fourProxDist, const glm::vec2* pos, const std::vector<float>* posAccum);
void compFourProxAbs(std::array<float, 12>* fourProxAbs, const glm::vec2* pos, const std::vector<float>* posAccum);
// After determining the four closest points orders them by bottom left, bottom right, upper left, and then upper right
float compLocalZ(std::array<float, 12>* fourProx, const glm::vec2* pos);
float compLocalZ(std::array<float, 12>* fourProxPos, std::array<float, 4>* fourProxDist);