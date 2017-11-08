#include "Geometry.h"

void GL4_CellGrid::create(GLfloat cellSize, GLfloat spacing, GLuint xCount, GLuint yCount){
    GLfloat startPt[2];
    startPt[0] = -1 * (((cellSize + spacing) * xCount) / 2.0);
    startPt[1] = -1 * (((cellSize + spacing) * yCount) / 2.0);

    std::vector<GLfloat> posAccum;
    std::vector<GLuint> indexAccum;
    GLuint vertexID = 0;
    
    for(GLuint currentCol = 0; currentCol < yCount; currentCol++){
        GLfloat yOffset = startPt[1] + ((cellSize + spacing) * currentCol);
        for(GLuint currentRow = 0; currentRow < xCount; currentRow++){
            GLfloat xOffset = startPt[0] + ((cellSize + spacing) * currentRow);
            posAccum.push_back(xOffset);
            posAccum.push_back(yOffset);
            posAccum.push_back(0.0);
            posAccum.push_back(xOffset + cellSize);
            posAccum.push_back(yOffset);
            posAccum.push_back(0.0);
            posAccum.push_back(xOffset);
            posAccum.push_back(yOffset + cellSize);
            posAccum.push_back(0.0);
            posAccum.push_back(xOffset + cellSize);
            posAccum.push_back(yOffset + cellSize);
            posAccum.push_back(0.0);

            indexAccum.push_back((currentCol * currentRow) + (currentRow * 6));
            indexAccum.push_back((currentCol * currentRow) + (currentRow * 6) + 1);
            indexAccum.push_back((currentCol * currentRow) + (currentRow * 6) + 2);
            indexAccum.push_back((currentCol * currentRow) + (currentRow * 6));
            indexAccum.push_back((currentCol * currentRow) + (currentRow * 6) + 1);
            indexAccum.push_back((currentCol * currentRow) + (currentRow * 6));

            vertexID++;
        }
    }

    GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GL4_CellGrid::feed[GL4_CellGrid::VAO] = VAO;

	GLuint feedBuffers[3];
	glGenBuffers(3, feedBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, feedBuffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAccum.size() * sizeof(GLuint), &indexAccum[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, posAccum.size() * sizeof(GLfloat), &posAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    GL4_CellGrid::vertexCount = vertexID;
    GL4_CellGrid::feed[GL4_CellGrid::EBO] = feedBuffers[0];
    GL4_CellGrid::feed[GL4_CellGrid::feedPos] = feedBuffers[1];

    glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_CellGrid::drawXI(){
    glBindVertexArray(GL4_CellGrid::feed[GL4_CellGrid::VAO]);
    // glDrawElements(GL_TRIANGLES, GL4_CellGrid::vertexCount * 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_POINTS, 0, GL4_CellGrid::vertexCount * 6);
    glBindVertexArray(0);
}