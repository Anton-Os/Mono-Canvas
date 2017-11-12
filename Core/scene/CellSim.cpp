#include "Scene.h"

#include <cstdint>

void Scene_CellSim::gen_startPoints(unsigned int count){
    for(unsigned int currentCell = 0; currentCell < count; currentCell++){
        if(currentCell % 5 == 0) // Marked for change, make relative to count arg
            Scene_CellSim::cellStates[currentCell] = Scene_CellSim::alive;
        else
            Scene_CellSim::cellStates[currentCell] = Scene_CellSim::untouched;
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
        if(chance < probability)
            Scene_CellSim::cellStates[currentCell] = Scene_CellSim::alive;
        else
            Scene_CellSim::cellStates[currentCell] = Scene_CellSim::untouched;
    }
    return;
}

/* void Scene_CellSim::scanGrid(){
    for(unsigned int currentCell = 0; currentCell < Scene_CellSim::cellStates.size(); currentCell++){
        if(currentCell < Scene_CellSim::xyCount) Scene_CellSim::cellStates[currentCell] = Scene_CellSim::dead;
        else if(currentCell >= Scene_CellSim::cellStates.size() - Scene_CellSim::xyCount) Scene_CellSim::cellStates[currentCell] = Scene_CellSim::born;
    }
    return;
} */

void Scene_CellSim::scanGrid(){
    unsigned int proxEight[8];
    for(unsigned int currentCell = 0; currentCell < Scene_CellSim::cellStates.size(); currentCell++){
        if(currentCell < Scene_CellSim::xyCount || 
           currentCell >= Scene_CellSim::cellStates.size() - Scene_CellSim::xyCount ||
           currentCell % Scene_CellSim::xyCount == 0 ||
           (currentCell + 1) % Scene_CellSim::xyCount == 0 ) {
               continue;
        }
        uint8_t deadCount = 0;
        uint8_t aliveCount = 0;
        proxEight[0] = Scene_CellSim::cellStates[currentCell - Scene_CellSim::xyCount - 1];
        proxEight[1] = Scene_CellSim::cellStates[currentCell - Scene_CellSim::xyCount];
        proxEight[2] = Scene_CellSim::cellStates[currentCell - Scene_CellSim::xyCount + 1];
        proxEight[3] = Scene_CellSim::cellStates[currentCell - 1];
        proxEight[4] = Scene_CellSim::cellStates[currentCell + 1];
        proxEight[5] = Scene_CellSim::cellStates[currentCell + Scene_CellSim::xyCount - 1];
        proxEight[6] = Scene_CellSim::cellStates[currentCell + Scene_CellSim::xyCount];
        proxEight[7] = Scene_CellSim::cellStates[currentCell + Scene_CellSim::xyCount + 1];
        for(unsigned int proxElem = 0; proxElem < 8; proxElem++){
            if(proxEight[proxElem] == Scene_CellSim::alive) aliveCount++;
            else deadCount++;
        }
        if(aliveCount < deadCount) Scene_CellSim::cellStates[currentCell] = Scene_CellSim::born;
    }
    return;
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
}