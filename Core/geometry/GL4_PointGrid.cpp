#include "Geometry.h"

/* void GL4_PointGrid::create(GLuint xDimension, GLuint xCount, GLuint yDimension, GLuint yCount){
	GLfloat xStride = (float)xDimension / (float)xCount;
	GLfloat yStride = (float)yDimension / (float)yCount;

	std::vector<float> posAccum;

	GLfloat xOffset = 0.0;
	GLfloat yOffset = 0.0;

	for(GLuint currentCol = 0; currentCol < yCount; currentCol++){
		xOffset = 0.0;
		for(GLuint currentRow = 0; currentRow < xCount; currentRow++){
			posAccum.push_back(xOffset);
			posAccum.push_back(yOffset);
			posAccum.push_back(0.0);

			xOffset += xStride;
		}
		yOffset += yStride;
	}

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, posAccum.size() * sizeof(GLfloat), &posAccum[0], GL_STATIC_DRAW);
	// GLfloat zero[3] = {0.0, 0.0, 0.0};
	// glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3, &zero[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	GL4_PointGrid::vertexCount = xCount * yCount;
	GL4_PointGrid::feed[GL4_PointGrid::VAO] = VAO;
	GL4_PointGrid::feed[GL4_PointGrid::feedPos] = buffer;

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
} */

void GL4_PointGrid::create(GLuint xDimension, GLuint xCount, GLuint yDimension, GLuint yCount) {
	GLfloat xStride = (float)xDimension / (float)xCount;
	GLfloat yStride = (float)yDimension / (float)yCount;

	std::vector<float> posAccum;

	GLfloat xOffset = 0.0;
	GLfloat yOffset = 0.0;

	for (GLuint currentCol = 0; currentCol < yCount; currentCol++) {
		xOffset = 0.0;
		for (GLuint currentRow = 0; currentRow < xCount; currentRow++) {
			posAccum.push_back(xOffset);
			posAccum.push_back(yOffset);
			posAccum.push_back(0.0);

			xOffset += xStride;
		}
		yOffset += yStride;
	}

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GL4_PointGrid::feed[GL4_PointGrid::VAO] = VAO;

	GLuint feedBuffer;
	glGenBuffers(1, &feedBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffer);
	glBufferData(GL_ARRAY_BUFFER, posAccum.size() * sizeof(GLfloat), &posAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	GL4_PointGrid::feed[GL4_PointGrid::feedPos] = feedBuffer;

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void GL4_PointGrid::draw(){
    glBindVertexArray(GL4_PointGrid::feed[GL4_PointGrid::VAO]);
    glDrawArrays(GL_POINTS, 0, GL4_PointGrid::vertexCount);
	glBindVertexArray(0);
}

void GL4_PointGrid::draw(float pointSize){
	glPointSize(pointSize);
    glBindVertexArray(GL4_PointGrid::feed[GL4_PointGrid::VAO]);
    glDrawArrays(GL_POINTS, 0, GL4_PointGrid::vertexCount);
	glBindVertexArray(0);
}