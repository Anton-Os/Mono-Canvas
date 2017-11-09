#include "Scene.h"

/* void Scene_CellSim::gen_startPoints(unsigned int count){
    Scene_CellSim::cellStates.resize(count);

    for(unsigned int currentCell = 0; currentCell < count; currentCell++){
        Scene_CellSim::cellStates[currentCell] = Scene_CellSim::alive;
    }
} */

void Scene_CellSim::gen_startPoints(unsigned int count) {
	Scene_CellSim::cellStates.resize(count * 2);

	for (unsigned int currentCell = 0; currentCell < count * 2; currentCell += 2) {
		Scene_CellSim::cellStates[currentCell] = Scene_CellSim::alive;
		Scene_CellSim::cellStates[currentCell] = Scene_CellSim::dead;
	}
}

void Scene_CellSim::updateStates(){
    glBindVertexArray(Scene_CellSim::VAO);

    GLuint stateBuffer;
    glGenBuffers(1, &stateBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, stateBuffer);
	glBufferData(GL_ARRAY_BUFFER, Scene_CellSim::cellStates.size() * sizeof(GLuint), &Scene_CellSim::cellStates[0], GL_STATIC_DRAW);
	glVertexAttribPointer(6, 2, GL_UNSIGNED_INT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(6);
    /* glVertexAttribI1uiv(6, Scene_CellSim::cellStates.data());
    glEnableVertexAttribArray(6); */
    glBindVertexArray(0);
}