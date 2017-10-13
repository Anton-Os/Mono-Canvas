#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cfloat>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void compFourProx(std::array<float, 12>* fourProx, const glm::vec2* pos, const std::vector<float>* posAccum);
void compFourProxAbs(std::array<float, 12>* fourProxAbs, const glm::vec2* pos, const std::vector<float>* posAccum);
// After determining the four closest points orders them by bottom left, bottom right, upper left, and then upper right
float compLocalZ(std::array<float, 12>* fourProx, const glm::vec2* pos);