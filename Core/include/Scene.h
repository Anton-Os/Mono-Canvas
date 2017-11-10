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
    Scene_CellSim(GL4_BumpGrid* bumpGrid){
        VAO = bumpGrid->feed[bumpGrid->VAO];
        rows = bumpGrid->get_rowCount();
        columns = bumpGrid->get_colCount();
        Scene_CellSim::cellStates.resize(bumpGrid->get_vertexCount());
        gen_startPoints(bumpGrid->get_vertexCount());
    }
    Scene_CellSim(GL4_BumpGrid* bumpGrid, float probability){
        VAO = bumpGrid->feed[bumpGrid->VAO];
        rows = bumpGrid->get_rowCount();
        columns = bumpGrid->get_colCount();
        Scene_CellSim::cellStates.resize(bumpGrid->get_vertexCount());
        gen_startPoints(bumpGrid->get_vertexCount(), probability);
    }
    enum stateParams { dead, alive };
    void scanGrid();
    void updateStates();
private:
    unsigned int VAO;
    unsigned int rows; unsigned int columns;
    std::vector<unsigned int> cellStates;
    void gen_startPoints(unsigned int count);
    void gen_startPoints(unsigned int count, float probability);
};