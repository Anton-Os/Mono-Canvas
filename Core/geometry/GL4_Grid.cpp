#include "Geometry.h"

void GL4_Grid::create(GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount) {
	GLfloat uTex = 0.0; GLfloat vTex = 0.0;
	GLfloat colSize = (GLfloat)yDimension / (GLfloat)colCount;
	GLfloat rowSize = (GLfloat)xDimension / (GLfloat)rowCount;
	bool lastRow = false; bool lastCol = false;

	std::vector<GLfloat> posAccum;
	std::vector<GLfloat> texCoordAccum;
	std::vector<GLuint> indexAccum;

	GLuint vertexID = 0;
	GLuint indexID = 0;

	GLfloat rowOffset = -1 * (GLfloat)xDimension / 2;	
	GLfloat colOffset = -1 * (GLfloat)yDimension / 2;
	for (GLuint currentCol = 0; currentCol < colCount; currentCol++) {
		colOffset += colSize;
		if (currentCol >= (yDimension / 2) - colSize) lastCol = true;
		rowOffset = -1 * (GLfloat)xDimension / 2;
		for (GLuint currentRow = 0; currentRow < rowCount; currentRow++) {
			rowOffset += rowSize;
			posAccum.push_back(rowOffset);
			posAccum.push_back(colOffset);
			posAccum.push_back(0.0f);

			if (vertexID % (rowCount * 2) < rowCount) uTex = 0.0;
			else uTex = 1.0;
			texCoordAccum.push_back(uTex);
			if (vertexID % 2 == 0) vTex = 0.0;
			else vTex = 1.0;
			texCoordAccum.push_back(vTex);

			if (currentRow >= (xDimension / 2) - rowSize) lastRow = true;
			if (!lastRow && !lastCol) {
				indexAccum.push_back(vertexID + 1);
				indexAccum.push_back(vertexID);
				indexAccum.push_back(vertexID + rowCount + 1);
				indexAccum.push_back(vertexID + 1);
				indexAccum.push_back(vertexID + rowCount + 2);
				indexAccum.push_back(vertexID + rowCount + 1);

				indexID++;
			}
			else lastRow = false;
			vertexID++;
		}
	}

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GL4_Grid::feed[GL4_Grid::VAO] = VAO;

	GLuint feedBuffers[3];
	glGenBuffers(3, feedBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, feedBuffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAccum.size() * sizeof(GLuint), &indexAccum[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, posAccum.size() * sizeof(GLfloat), &posAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[2]);
	glBufferData(GL_ARRAY_BUFFER, texCoordAccum.size() * sizeof(GLfloat), &texCoordAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(1);
	
	GL4_Grid::vertexCount = vertexID;
	GL4_Grid::indexCount = indexID;
	GL4_Grid::feed[GL4_Grid::EBO] = feedBuffers[0];
	GL4_Grid::feed[GL4_Grid::feedPos] = feedBuffers[1];
	GL4_Grid::feed[GL4_Grid::feedTexCoord] = feedBuffers[2];

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_Grid::map(std::vector<GLfloat>* posAccum){
    glBindVertexArray(GL4_Grid::feed[GL4_Grid::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_Grid::feed[GL4_Grid::feedPos]);
    GLfloat* posData = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
	posAccum->resize(GL4_Grid::vertexCount * 3);

    for(GLuint posElem = 0; posElem < posAccum->size(); posElem++){
		posAccum->at(posElem) = *(posData + posElem);
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(0);
}

void GL4_Grid::map(std::vector<GLuint>* indexAccum){
    glBindVertexArray(GL4_Grid::feed[GL4_Grid::VAO]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL4_Grid::feed[GL4_Grid::EBO]);
    GLuint* indexData = (GLuint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
	indexAccum->resize(GL4_Grid::indexCount * 6);

    for(GLuint indexElem = 0; indexElem < indexAccum->size(); indexElem++){
		indexAccum->at(indexElem) = *(indexData + indexElem);
    }

    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBindVertexArray(0);
}


void GL4_Grid::draw(){
    glBindVertexArray(GL4_Grid::feed[GL4_Grid::VAO]);
    glDrawElements(GL_TRIANGLES, GL4_Grid::vertexCount * 6, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_LINES, 0, GL4_Grid::vertexCount);
    glBindVertexArray(0);
}

void GL4_Grid::draw(GLenum drawMode){
    glBindVertexArray(GL4_Grid::feed[GL4_Grid::VAO]);
    glDrawElements(drawMode, GL4_Grid::vertexCount * 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_Grid::drawXI(GLenum drawMode){
	glBindVertexArray(GL4_Grid::feed[GL4_Grid::VAO]);
    glDrawArrays(drawMode, 0, GL4_Grid::vertexCount);
    glBindVertexArray(0);
}

void GL4_Grid::drawFixed(GLenum drawMode, GLuint indexCount){
    glBindVertexArray(GL4_Grid::feed[GL4_Grid::VAO]);
    if(indexCount > GL4_Grid::vertexCount * 6) glDrawElements(drawMode, GL4_Grid::vertexCount * 6, GL_UNSIGNED_INT, 0);
    else glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}