#include "Geometry.h"

void GL4_BumpGrid::create(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount) {
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GL4_BumpGrid::feed[GL4_BumpGrid::VAO] = VAO;

	GLfloat uTex = 0.0; GLfloat vTex = 0.0;
	GLfloat colSize = (GLfloat)yDimension / (GLfloat)colCount;
	GLfloat rowSize = (GLfloat)xDimension / (GLfloat)rowCount;
	bool lastRow = false; bool lastCol = false;

	std::vector<GLfloat> posAccum;
	std::vector<GLfloat> texCoordAccum;
	std::vector<GLuint> indexAccum;

	GLuint vertexID = 0;
	GLuint indexID = 0;
	srand(time(NULL));

	for (GLfloat currentCol = -1 * (GLfloat)yDimension / 2; currentCol <= (GLfloat)yDimension / 2; currentCol += colSize) {
		if (currentCol >= (yDimension / 2) - colSize) lastCol = true;
		for (GLfloat currentRow = -1 * (GLfloat)xDimension / 2; currentRow <= (GLfloat)xDimension / 2; currentRow += rowSize) {
			posAccum.push_back(currentRow);
			posAccum.push_back(currentCol);
			posAccum.push_back(((static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX)) * rise) - rise / 2);

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

	std::vector<GLfloat> nrmAccum;
	for (GLuint mpointIndexElem = 0; mpointIndexElem < vertexID; mpointIndexElem++) {
		nrmAccum.push_back(0.0f);
		nrmAccum.push_back(1.0f);
		nrmAccum.push_back(0.0f);
	}

	GLuint feedBuffers[4];
	glGenBuffers(4, feedBuffers);
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
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[3]);
	glBufferData(GL_ARRAY_BUFFER, nrmAccum.size() * sizeof(GLfloat), &nrmAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(2);

	GL4_BumpGrid::vertexCount = vertexID;
	GL4_BumpGrid::indexCount = indexID;
	GL4_BumpGrid::feed[GL4_BumpGrid::EBO] = feedBuffers[0];
	GL4_BumpGrid::feed[GL4_BumpGrid::feedPos] = feedBuffers[1];
	GL4_BumpGrid::feed[GL4_BumpGrid::feedTexCoord] = feedBuffers[2];
	GL4_BumpGrid::feed[GL4_BumpGrid::feedNormal] = feedBuffers[3];

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_BumpGrid::gen_midPointQ(std::vector<MidPointQuad>* midPoints){
    std::vector<float> posAccum;
    GL4_BumpGrid::map(&posAccum);
    std::vector<unsigned int> indexAccum;
    GL4_BumpGrid::map(&indexAccum);

    std::vector<unsigned int> midPointIndexAccum;
    midPointIndexAccum.resize(GL4_BumpGrid::indexCount * 4);

    for(GLuint indexSetElem = 0; indexSetElem < GL4_BumpGrid::indexCount; indexSetElem++){
        std::array<unsigned int, 6> indexSet = {indexAccum[indexSetElem * 6], indexAccum[indexSetElem * 6 + 1], indexAccum[indexSetElem * 6 + 2], indexAccum[indexSetElem * 6 + 3], indexAccum[indexSetElem * 6 + 4], indexAccum[indexSetElem * 6 + 5] };
        std::array<unsigned int, 4> midPointIndexSet = {UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX};
        unsigned int indexInc = 0;
        for(unsigned int indexElem = 0; indexInc < 4; indexElem++){
            if(indexSet[indexElem] != midPointIndexSet[0] && indexSet[indexElem] != midPointIndexSet[1] && indexSet[indexElem] != midPointIndexSet[2] && indexSet[indexElem] != midPointIndexSet[3]){
                midPointIndexSet[indexInc] = indexSet[indexElem];
                indexInc++;
            }
        }
        midPointIndexAccum[indexSetElem * 4] = midPointIndexSet[0];
        midPointIndexAccum[indexSetElem * 4 + 1] = midPointIndexSet[1];
        midPointIndexAccum[indexSetElem * 4 + 2] = midPointIndexSet[2];
        midPointIndexAccum[indexSetElem * 4 + 3] = midPointIndexSet[3];
    }

	MidPointQuad midPointQ;
	midPoints->resize(GL4_BumpGrid::indexCount);

	for (GLuint midPointIndexElem = 0; midPointIndexElem < GL4_BumpGrid::indexCount; midPointIndexElem++) {
		midPointQ.fourProx[0] = posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3];
		midPointQ.fourProx[1] = posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3 + 1];
		midPointQ.fourProx[2] = posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3 + 2];
		midPointQ.fourProx[3] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3];
		midPointQ.fourProx[4] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3 + 1];
		midPointQ.fourProx[5] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3 + 2];
		midPointQ.fourProx[6] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3];
		midPointQ.fourProx[7] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3 + 1];
		midPointQ.fourProx[8] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3 + 2];
		midPointQ.fourProx[9] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3];
		midPointQ.fourProx[10] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3 + 1];
		midPointQ.fourProx[11] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3 + 2];

		float avrgX = (posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3]) / 4;
		midPointQ.pos[0] = avrgX;
		float avrgY = (posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3 + 1] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3 + 1] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3 + 1] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3 + 1]) / 4;
		midPointQ.pos[1] = avrgY;
		float avrgZ = (posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3 + 2] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3 + 2] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3 + 2] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3 + 2]) / 4;
		midPointQ.pos[2] = avrgZ;
		midPoints->at(midPointIndexElem) = midPointQ;
	}
}

void GL4_BumpGrid::gen_midPoint45(std::vector<MidPoint45>* midPoints){
	std::vector<float> posAccum;
    GL4_BumpGrid::map(&posAccum);
    std::vector<unsigned int> indexAccum;
    GL4_BumpGrid::map(&indexAccum);

    std::vector<unsigned int> midPointIndexAccum;
    midPointIndexAccum.resize(GL4_BumpGrid::indexCount * 4);

    for(GLuint indexSetElem = 0; indexSetElem < GL4_BumpGrid::indexCount; indexSetElem++){
        std::array<unsigned int, 6> indexSet = {indexAccum[indexSetElem * 6], indexAccum[indexSetElem * 6 + 1], indexAccum[indexSetElem * 6 + 2], indexAccum[indexSetElem * 6 + 3], indexAccum[indexSetElem * 6 + 4], indexAccum[indexSetElem * 6 + 5] };
        std::array<unsigned int, 4> midPointIndexSet = {UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX};
        unsigned int indexInc = 0;
        for(unsigned int indexElem = 0; indexInc < 4; indexElem++){
            if(indexSet[indexElem] != midPointIndexSet[0] && indexSet[indexElem] != midPointIndexSet[1] && indexSet[indexElem] != midPointIndexSet[2] && indexSet[indexElem] != midPointIndexSet[3]){
                midPointIndexSet[indexInc] = indexSet[indexElem];
                indexInc++;
            }
        }
        midPointIndexAccum[indexSetElem * 4] = midPointIndexSet[0];
        midPointIndexAccum[indexSetElem * 4 + 1] = midPointIndexSet[1];
        midPointIndexAccum[indexSetElem * 4 + 2] = midPointIndexSet[2];
        midPointIndexAccum[indexSetElem * 4 + 3] = midPointIndexSet[3];
    }

	// MidPointQuad midPointQ;
	MidPoint45 midPoint45;
	midPoint45.threeIndex1[0] = 0;
	midPoint45.threeIndex1[1] = 1;
	midPoint45.threeIndex1[2] = 2;
	midPoint45.threeIndex2[0] = 1;
	midPoint45.threeIndex2[1] = 2;
	midPoint45.threeIndex2[2] = 3;

	midPoints->resize(GL4_BumpGrid::indexCount);

	for (GLuint midPointIndexElem = 0; midPointIndexElem < GL4_BumpGrid::indexCount; midPointIndexElem++) {
		midPoint45.fourProx[0] = posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3];
		midPoint45.fourProx[1] = posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3 + 1];
		midPoint45.fourProx[2] = posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3 + 2];
		midPoint45.fourProx[3] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3];
		midPoint45.fourProx[4] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3 + 1];
		midPoint45.fourProx[5] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3 + 2];
		midPoint45.fourProx[6] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3];
		midPoint45.fourProx[7] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3 + 1];
		midPoint45.fourProx[8] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3 + 2];
		midPoint45.fourProx[9] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3];
		midPoint45.fourProx[10] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3 + 1];
		midPoint45.fourProx[11] = posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3 + 2];

		float avrgX = (posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3]) / 4;
		midPoint45.pos[0] = avrgX;
		float avrgY = (posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3 + 1] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3 + 1] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3 + 1] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3 + 1]) / 4;
		midPoint45.pos[1] = avrgY;
		float avrgZ = (posAccum[midPointIndexAccum[midPointIndexElem * 4] * 3 + 2] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 1] * 3 + 2] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 2] * 3 + 2] +
			posAccum[midPointIndexAccum[midPointIndexElem * 4 + 3] * 3 + 2]) / 4;
		midPoint45.pos[2] = avrgZ;

		avrgX =  (midPoint45.fourProx[midPoint45.threeIndex1[0] * 3] + 
			midPoint45.fourProx[midPoint45.threeIndex1[1] * 3] +
			midPoint45.fourProx[midPoint45.threeIndex1[2] * 3]) / 3;
		midPoint45.t1[0] = avrgX;
		avrgY =  (midPoint45.fourProx[midPoint45.threeIndex1[0] * 3 + 1] + 
			midPoint45.fourProx[midPoint45.threeIndex1[1] * 3 + 1] +
			midPoint45.fourProx[midPoint45.threeIndex1[2] * 3 + 1]) / 3;
		midPoint45.t1[1] = avrgY;
		avrgZ =  (midPoint45.fourProx[midPoint45.threeIndex1[0] * 3 + 2] + 
			midPoint45.fourProx[midPoint45.threeIndex1[1] * 3 + 2] +
			midPoint45.fourProx[midPoint45.threeIndex1[2] * 3 + 2]) / 3;	
		midPoint45.t1[2] = avrgZ;

		avrgX =  (midPoint45.fourProx[midPoint45.threeIndex2[0] * 3] + 
			midPoint45.fourProx[midPoint45.threeIndex2[1] * 3] +
			midPoint45.fourProx[midPoint45.threeIndex2[2] * 3]) / 3;
		midPoint45.t2[0] = avrgX;
		avrgY =  (midPoint45.fourProx[midPoint45.threeIndex2[0] * 3 + 1] + 
			midPoint45.fourProx[midPoint45.threeIndex2[1] * 3 + 1] +
			midPoint45.fourProx[midPoint45.threeIndex2[2] * 3 + 1]) / 3;
		midPoint45.t2[1] = avrgY;
		avrgZ =  (midPoint45.fourProx[midPoint45.threeIndex2[0] * 3 + 2] + 
			midPoint45.fourProx[midPoint45.threeIndex2[1] * 3 + 2] +
			midPoint45.fourProx[midPoint45.threeIndex2[2] * 3 + 2]) / 3;	
		midPoint45.t2[2] = avrgZ;

		midPoints->at(midPointIndexElem) = midPoint45;
	}
}

void GL4_BumpGrid::gen_midPointT(std::vector<MidPointTrig>* midPoints){
    std::vector<float> posAccum;
    GL4_BumpGrid::map(&posAccum);
    std::vector<unsigned int> indexAccum;
    GL4_BumpGrid::map(&indexAccum);

	MidPointTrig midPointT;
	midPoints->resize(GL4_BumpGrid::indexCount * 2);

	for (GLuint midPointIndexElem = 0; midPointIndexElem < GL4_BumpGrid::indexCount * 2; midPointIndexElem++) {
		midPointT.threeProx[0] = posAccum[indexAccum[midPointIndexElem * 3] * 3];
		midPointT.threeProx[1] = posAccum[indexAccum[midPointIndexElem * 3] * 3 + 1];
		midPointT.threeProx[2] = posAccum[indexAccum[midPointIndexElem * 3] * 3 + 2];
		midPointT.threeProx[3] = posAccum[indexAccum[midPointIndexElem * 3 + 1] * 3];
		midPointT.threeProx[4] = posAccum[indexAccum[midPointIndexElem * 3 + 1] * 3 + 1];
		midPointT.threeProx[5] = posAccum[indexAccum[midPointIndexElem * 3 + 1] * 3 + 2];
		midPointT.threeProx[6] = posAccum[indexAccum[midPointIndexElem * 3 + 2] * 3];
		midPointT.threeProx[7] = posAccum[indexAccum[midPointIndexElem * 3 + 2] * 3 + 1];
		midPointT.threeProx[8] = posAccum[indexAccum[midPointIndexElem * 3 + 2] * 3 + 2];

		float avrgX = (posAccum[indexAccum[midPointIndexElem * 3] * 3] +
			posAccum[indexAccum[midPointIndexElem * 3 + 1] * 3] +
			posAccum[indexAccum[midPointIndexElem * 3 + 2] * 3]) / 3;
		midPointT.pos[0] = avrgX;
		float avrgY = (posAccum[indexAccum[midPointIndexElem * 3] * 3 + 1] +
			posAccum[indexAccum[midPointIndexElem * 3 + 1] * 3 + 1] +
			posAccum[indexAccum[midPointIndexElem * 3 + 2] * 3 + 1]) / 3;
		midPointT.pos[1] = avrgY;
		float avrgZ = (posAccum[indexAccum[midPointIndexElem * 3] * 3 + 2] +
			posAccum[indexAccum[midPointIndexElem * 3 + 1] * 3 + 2] +
			posAccum[indexAccum[midPointIndexElem * 3 + 2] * 3 + 2]) / 3;
		midPointT.pos[2] = avrgZ;
		midPoints->at(midPointIndexElem) = midPointT;
	}
}

void GL4_BumpGrid::map(std::vector<GLfloat>* posAccum){
    glBindVertexArray(GL4_BumpGrid::feed[0]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_BumpGrid::feed[GL4_BumpGrid::feedPos]);
    GLfloat* posData = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
	posAccum->resize(GL4_BumpGrid::vertexCount * 3);

    for(GLuint posElem = 0; posElem < posAccum->size(); posElem++){
		posAccum->at(posElem) = *(posData + posElem);
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(0);
}

void GL4_BumpGrid::map(std::vector<GLuint>* indexAccum){
    glBindVertexArray(GL4_BumpGrid::feed[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL4_BumpGrid::feed[GL4_BumpGrid::EBO]);
    GLuint* indexData = (GLuint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
	indexAccum->resize(GL4_BumpGrid::indexCount * 6);

    for(GLuint indexElem = 0; indexElem < indexAccum->size(); indexElem++){
		indexAccum->at(indexElem) = *(indexData + indexElem);
    }

    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBindVertexArray(0);
}

void GL4_BumpGrid::draw(){
    glBindVertexArray(GL4_BumpGrid::feed[0]);
    glDrawElements(GL_TRIANGLES, GL4_BumpGrid::vertexCount * 6, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_LINES, 0, GL4_BumpGrid::vertexCount);
    glBindVertexArray(0);
}

void GL4_BumpGrid::draw(GLenum drawMode){
    glBindVertexArray(GL4_BumpGrid::feed[0]);
    glDrawElements(drawMode, GL4_BumpGrid::vertexCount * 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_BumpGrid::drawFixed(GLenum drawMode, GLuint indexCount){
    glBindVertexArray(GL4_BumpGrid::feed[0]);
    if(indexCount > GL4_BumpGrid::vertexCount * 6) glDrawElements(drawMode, GL4_BumpGrid::vertexCount * 6, GL_UNSIGNED_INT, 0);
    else glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}