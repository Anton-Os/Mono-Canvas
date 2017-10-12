#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cfloat>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// std::array<unsigned int, 4> compFourClosest(glm::vec2* pos, std::vector<float>* posAccum);
void compFourProx(std::array<float, 12>* fourProx, const glm::vec2* pos, const std::vector<float>* posAccum);
// float compHeight(std::array<unsigned int, 4> fourClosest);
float compLocalZ(std::array<float, 12>* fourProx, const glm::vec2* pos);