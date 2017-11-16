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
    float calcZ(const MidPointTrig* midPoint, const glm::vec2* posXY);
    bool trigFlip(const MidPointTrig* midPoint, const glm::vec2* posXY);
    glm::vec3 calcV90(const MidPointTrig* midPoint);
};

class Scene_CellSim {
public:
    Scene_CellSim(GL4_Grid* grid){
        if(! grid->get_isSquare())
            std::cout << "! Grid not a perfect square, use different constructor" << std::endl;
        VAO = grid->feed[grid->VAO];
        Scene_CellSim::cellStates.resize(grid->get_vertexCount());
        Scene_CellSim::prevCellStates.resize(grid->get_vertexCount());
        xyCount = std::sqrt(grid->get_vertexCount());
        gen_startPoints(grid->get_vertexCount());
    }
    Scene_CellSim(GL4_Grid* grid, float probability){
        if(! grid->get_isSquare())
            std::cout << "! Grid not a perfect square, use different constructor" << std::endl;
        VAO = grid->feed[grid->VAO];
        Scene_CellSim::cellStates.resize(grid->get_vertexCount());
        Scene_CellSim::prevCellStates.resize(grid->get_vertexCount());
        xyCount = std::sqrt(grid->get_vertexCount());
        gen_startPoints(grid->get_vertexCount(), probability);
    }
    enum stateParams { untouched, alive, dead, born, quickDead };
    void scanGrid();
    void gen_proxPoints();
    void updateStates();
private:
    unsigned int VAO;
    GLuint xyCount;
    std::vector<unsigned int> cellStates;
    std::vector<unsigned int> prevCellStates;
    void gen_startPoints(unsigned int count);
    void gen_startPoints(unsigned int count, float probability);
    // void gen_proxPoints(const std::array<unsigned int, 8>* proxStates);
    unsigned int determineState(unsigned int cellState, const std::array<unsigned int, 8>* proxStates);
    unsigned int determineState_v2(unsigned int cellState, const std::array<unsigned int, 8>* proxStates);
};