#include "Common.h"

#include <vector>

#include <assimp/cimport.h>
#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// From Mesh.cpp

struct Point {
    std::array<GLfloat, 3> pos;
    std::array<GLubyte, 4> color;
    std::array<GLfloat, 2> texCoord;
    std::array<GLfloat, 3> normal;
};

struct Texture {
    GLuint texId;
    const char* texFile;
};