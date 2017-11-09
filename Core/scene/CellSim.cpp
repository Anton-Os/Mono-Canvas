#include "Scene.h"

void Scene_CellSim::gen_startPoints(unsigned int count){
    for(unsigned int currentCell = 0; currentCell < count; currentCell++){
        Scene_CellSim::cellStates[currentCell] = Scene_CellSim::alive;
    }
}

/*void Scene_CellSim::gen_startPoints(unsigned int count, unsigned int sparsity){
    unsigned int maxStride = count / sparsity;
    unsigned int currentOffset = 0;

    for(unsigned int currentStride = 0; currentStride < maxStride; currentOffset++){
        if(currentOffset >= maxStride) currentOffset = 0;
        
        unsigned int randomCell = (unsigned int)((static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX)) * maxStride);
        for(unsigned int currentCell = 0; currentCell < maxStride; currentCell++){
            if(currentCell != randomCell) Scene_CellSim::cellStates[currentOffset * maxStride + currentCell] = Scene_CellSim::dead;
            else Scene_CellSim::cellStates[currentOffset * maxStride + currentCell] = Scene_CellSim::alive;
        }
    }
} */


void Scene_CellSim::updateStates(){
    glBindVertexArray(Scene_CellSim::VAO);

    GLuint cellStateBuffer;
	glGenBuffers(1, &cellStateBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, cellStateBuffer);
	glBufferData(GL_ARRAY_BUFFER, Scene_CellSim::cellStates.size() * sizeof(GLuint), &Scene_CellSim::cellStates[0], GL_STATIC_DRAW);
	glVertexAttribIPointer(4, 1, GL_UNSIGNED_INT, 0, (GLvoid*)0);
	glEnableVertexAttribArray(4);
    glBindVertexArray(0);
}