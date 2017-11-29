#ifndef GEOMETRY_H
    #include "geometry/GL4_Grid.hpp"
    #define GEOMETRY_H
#endif

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
