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

struct MidPointTrig {
    float pos[3];
    float threeProx[9];
};

struct MidPointQuad {
    float pos[3];
    float fourProx[12];
};

struct MidPoint45 {
    float pos[3];
    float fourProx[12];

    float t1[3];
    short unsigned int threeIndex1[3];

    float t2[3];
    short unsigned int threeIndex2[3];
};

class GL4_Object3D {
public:
    glm::mat4 relMatrix;
    GLuint get_vertexCount(){ return vertexCount; }
    // drawXI();
    // drawXI(GLenum drawMode);
    // drawFixedXI(GLenum drawMode, GLuint vertexCount);
    // drawPartXI(GLenum drawMode, GLuint part, GLuint whole);
protected:
    GLuint vertexCount;
};