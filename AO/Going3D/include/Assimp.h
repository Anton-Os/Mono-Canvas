#include "Common.h"

#include <vector>

#include <assimp/cimport.h>
#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Point {
    std::array<GLfloat, 3> pos;
    std::array<GLfloat, 4> color;
    std::array<GLfloat, 2> texCoord;
    std::array<GLfloat, 3> normal;
};

class Model {
public:
    int data;
    Model(){
        std::cout << "I got created! " << std::endl;
    }
};

int assimpImportCPP(const std::string& pFile);
// int loadModelData(std::vector<Point> dataToLoad);
int loadModelData(int* a);
