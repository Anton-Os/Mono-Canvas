#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <array>
#include <limits>
#include <climits>
#include <bitset>
#include <algorithm>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct vertexFeed {
    unsigned int attribCount = 3;
    std::vector<float> pos;
};

struct vertexFeedIdx {
    unsigned int attribCount = 3;
    std::vector<float> pos;
    std::vector<unsigned int> idx;
};