#include "scene/CellSim.hpp"

#include <cstdint>

void Scene_CellSim::gen_startPoints(unsigned int count){
    for(unsigned int currentCell = 0; currentCell < count; currentCell++){
        if(currentCell % 5 == 0) Scene_CellSim::cellStates[currentCell] = Scene_CellSim::alive;
        else Scene_CellSim::cellStates[currentCell] = Scene_CellSim::untouched;
    }
}

void Scene_CellSim::gen_startPoints(unsigned int count, float probability){
    if(probability > 1.0 || probability < 0.0){
        std::cerr << "Scene_CellSim::gen_startPoints() needs a probability between 0.0 (no chance) or 1.0 (always spawn)" << std::endl;
        return;
    }
    srand(time(NULL));
    for(unsigned int currentCell = 0; currentCell < count; currentCell++){
        if(currentCell < Scene_CellSim::xyCount || 
           currentCell >= Scene_CellSim::cellStates.size() - Scene_CellSim::xyCount ||
           currentCell % Scene_CellSim::xyCount == 0 ||
           (currentCell + 1) % Scene_CellSim::xyCount == 0 ) {
               continue;
        }
        float chance = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
        if(chance < probability) Scene_CellSim::cellStates[currentCell] = Scene_CellSim::alive;
        else Scene_CellSim::cellStates[currentCell] = Scene_CellSim::untouched;
    }
    return;
}

/* void Scene_CellSim::gen_proxPoints(const std::array<unsigned int, 8>* proxStates){
    Scene_CellSim::cellStates[proxStat]
} */

void Scene_CellSim::gen_proxPoints(){
    for(unsigned int currentCell = 0; currentCell < Scene_CellSim::prevCellStates.size(); currentCell++){
        if(currentCell < Scene_CellSim::xyCount || 
           currentCell >= Scene_CellSim::prevCellStates.size() - Scene_CellSim::xyCount ||
           currentCell % Scene_CellSim::xyCount == 0 ||
           (currentCell + 1) % Scene_CellSim::xyCount == 0 ) {
               continue;
        }
        if(Scene_CellSim::cellStates[currentCell] == Scene_CellSim::alive){
            Scene_CellSim::cellStates[currentCell - Scene_CellSim::xyCount - 1] = Scene_CellSim::quickDead;
            Scene_CellSim::cellStates[currentCell - Scene_CellSim::xyCount] = Scene_CellSim::quickDead;
            Scene_CellSim::cellStates[currentCell - Scene_CellSim::xyCount + 1] = Scene_CellSim::quickDead;
            Scene_CellSim::cellStates[currentCell - 1] = Scene_CellSim::quickDead;
            Scene_CellSim::cellStates[currentCell + 1] = Scene_CellSim::quickDead;
            Scene_CellSim::cellStates[currentCell + Scene_CellSim::xyCount - 1] = Scene_CellSim::quickDead;
            Scene_CellSim::cellStates[currentCell + Scene_CellSim::xyCount] = Scene_CellSim::quickDead;
            Scene_CellSim::cellStates[currentCell + Scene_CellSim::xyCount + 1] = Scene_CellSim::quickDead;
        }   
    }
}

void Scene_CellSim::scanGrid(){
    std::array<unsigned int, 8> proxEight;
    for(unsigned int currentCell = 0; currentCell < Scene_CellSim::prevCellStates.size(); currentCell++){
        if(currentCell < Scene_CellSim::xyCount || 
           currentCell >= Scene_CellSim::prevCellStates.size() - Scene_CellSim::xyCount ||
           currentCell % Scene_CellSim::xyCount == 0 ||
           (currentCell + 1) % Scene_CellSim::xyCount == 0 ) {
               continue;
        }
        proxEight[0] = Scene_CellSim::prevCellStates[currentCell - Scene_CellSim::xyCount - 1];
        proxEight[1] = Scene_CellSim::prevCellStates[currentCell - Scene_CellSim::xyCount];
        proxEight[2] = Scene_CellSim::prevCellStates[currentCell - Scene_CellSim::xyCount + 1];
        proxEight[3] = Scene_CellSim::prevCellStates[currentCell - 1];
        proxEight[4] = Scene_CellSim::prevCellStates[currentCell + 1];
        proxEight[5] = Scene_CellSim::prevCellStates[currentCell + Scene_CellSim::xyCount - 1];
        proxEight[6] = Scene_CellSim::prevCellStates[currentCell + Scene_CellSim::xyCount];
        proxEight[7] = Scene_CellSim::prevCellStates[currentCell + Scene_CellSim::xyCount + 1];
        Scene_CellSim::cellStates[currentCell] = determineState(Scene_CellSim::prevCellStates[currentCell], &proxEight);
    }
    return;
}

unsigned int Scene_CellSim::determineState(unsigned int cellState, const std::array<unsigned int, 8>* proxStates){
    uint8_t goodNeighbors = 0;
    uint8_t badNeighbors = 0;
    for(unsigned int proxElem = 0; proxElem < 8; proxElem++){
        if(proxStates->at(proxElem) == Scene_CellSim::alive || 
           proxStates->at(proxElem) == Scene_CellSim::born)
           goodNeighbors++;
        else badNeighbors++;
    }
    if(cellState == Scene_CellSim::alive){
        if(goodNeighbors > 1 && goodNeighbors < 4) return cellState;
        else return Scene_CellSim::untouched;
    } else if(cellState == Scene_CellSim::born){
        if(goodNeighbors > 1 && goodNeighbors < 4) return Scene_CellSim::alive;
        else return Scene_CellSim::untouched;
    } else if(cellState == Scene_CellSim::untouched){
        // if(goodNeighbors > 1 && goodNeighbors < 4) return Scene_CellSim::born;
        if(goodNeighbors == 3) return Scene_CellSim::born;
        else return cellState;
    }
}
unsigned int Scene_CellSim::determineState_v2(unsigned int cellState, const std::array<unsigned int, 8>* proxStates){
    uint8_t goodNeighbors = 0;
    uint8_t badNeighbors = 0;
    for(unsigned int proxElem = 0; proxElem < 8; proxElem++){
        if(proxStates->at(proxElem) == Scene_CellSim::alive || 
           proxStates->at(proxElem) == Scene_CellSim::born)
           goodNeighbors++;
        else badNeighbors++;
    }
    if(cellState == Scene_CellSim::alive){
        if(goodNeighbors > 1 && goodNeighbors < 4) return cellState;
        else return Scene_CellSim::dead;
    } else if(cellState == Scene_CellSim::born){
        if(goodNeighbors > 1 && goodNeighbors < 4) return Scene_CellSim::alive;
        else return Scene_CellSim::quickDead;
    } else {
        if(goodNeighbors > 1 && goodNeighbors < 4) return Scene_CellSim::born;
        else return cellState;
    }
}

void Scene_CellSim::updateStates(){
    glBindVertexArray(Scene_CellSim::VAO);

    GLuint cellStateBuffer;
	glGenBuffers(1, &cellStateBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cellStateBuffer);
	glBufferData(GL_ARRAY_BUFFER, Scene_CellSim::cellStates.size() * sizeof(GLuint), &Scene_CellSim::cellStates[0], GL_STATIC_DRAW);
	glVertexAttribIPointer(5, 1, GL_UNSIGNED_INT, 0, (GLvoid*)0);
	glEnableVertexAttribArray(5);
    glBindVertexArray(0);

    Scene_CellSim::prevCellStates.swap(Scene_CellSim::cellStates);
}