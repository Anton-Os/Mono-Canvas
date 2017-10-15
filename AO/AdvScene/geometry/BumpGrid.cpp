#include "Geometry.h"

/* void GL4_BumpGrid::create(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount){
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GL4_BumpGrid::feed[GL4_BumpGrid::VAO] = VAO;
    
    GLfloat colSize = (GLfloat)yDimension / (GLfloat)colCount;
    GLfloat rowSize = (GLfloat)xDimension / (GLfloat)rowCount;
    
    GL4_BumpGrid::vertexCount = rowCount * colCount;
    std::vector<GLuint> indexAccum(GL4_BumpGrid::vertexCount * 6);
    std::vector<GLfloat> posAccum(GL4_BumpGrid::vertexCount * 3);
    std::vector<GLfloat> texCoordAccum(GL4_BumpGrid::vertexCount * 2);
    std::vector<GLfloat> normalAccum(GL4_BumpGrid::vertexCount * 3);

    srand(time(NULL));
    GLuint vertexID = 0;
    for(GLfloat currentCol = -1 * (GLfloat)yDimension / 2; currentCol < (GLfloat)yDimension / 2; currentCol += colSize){
        for(GLfloat currentRow = -1 * (GLfloat)xDimension / 2; currentRow < (GLfloat)xDimension / 2; currentRow += rowSize){
            GLfloat rise = (static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX)) * rise;
            posAccum[vertexID * 3] = currentRow;
            posAccum[vertexID * 3 + 1] = currentCol;
            posAccum[vertexID * 3 + 2] = rise;
            std::cout << posAccum[vertexID * 3] << " " << posAccum[vertexID * 3 + 1] << " " << posAccum[vertexID * 3 + 2] << std::endl;
            
            if (vertexID % (rowCount * 2) < rowCount) texCoordAccum[vertexID * 2] = 0.0;
			else texCoordAccum[vertexID * 2] = 1.0;
			if (vertexID % 2 == 0) texCoordAccum[vertexID * 2 + 1] = 0.0;
			else texCoordAccum[vertexID * 2 + 1] = 1.0;

            indexAccum[vertexID * 6] = vertexID;
            indexAccum[vertexID * 6 + 1] = vertexID + 1;
            indexAccum[vertexID * 6 + 2] = vertexID + rowCount;
            indexAccum[vertexID * 6 + 3] = vertexID;
            indexAccum[vertexID * 6 + 4] = vertexID + rowCount + 1;
            indexAccum[vertexID * 6 + 5] = vertexID + rowCount;

            vertexID++;
        }
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
    // For Normals
    
    GL4_BumpGrid::feed[GL4_BumpGrid::EBO] = feedBuffers[0];
    GL4_BumpGrid::feed[GL4_BumpGrid::feedPos] = feedBuffers[1];
    GL4_BumpGrid::feed[GL4_BumpGrid::feedTexCoord] = feedBuffers[2];
    // GL4_BumpGrid::feed[GL4_BumpGrid::feedNormal] = feedBuffers[3];

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_BumpGrid::draw(){
    glBindVertexArray(GL4_BumpGrid::feed[GL4_BumpGrid::VAO]);
    // glDrawElements(GL_TRIANGLES, GL4_BumpGrid::vertexCount * 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, GL4_BumpGrid::vertexCount);
    glBindVertexArray(0);
} */

void GL4_BumpGrid::create(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount){
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
    srand(time(NULL));

    for(GLfloat currentCol = -1 * (GLfloat)yDimension / 2; currentCol <= (GLfloat)yDimension / 2; currentCol += colSize){
        if(currentCol >= (yDimension / 2) - colSize) lastCol = true;
         
        for(GLfloat currentRow = -1 * (GLfloat)xDimension / 2; currentRow <= (GLfloat)xDimension / 2; currentRow += rowSize){
            posAccum.push_back(currentRow);
            posAccum.push_back(currentCol);
            posAccum.push_back(((static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX)) * rise) - rise / 2);

			if (vertexID % (rowCount * 2) < rowCount) uTex = 0.0;
			else uTex = 1.0;
            texCoordAccum.push_back(uTex);
			if (vertexID % 2 == 0) vTex = 0.0;
			else vTex = 1.0;
            texCoordAccum.push_back(vTex);
            
            if(currentRow >= (xDimension / 2) - rowSize) lastRow = true;

            if(! lastRow && ! lastCol){
                indexAccum.push_back(vertexID + 1);
                indexAccum.push_back(vertexID);
                indexAccum.push_back(vertexID + rowCount + 1);
                indexAccum.push_back(vertexID + 1);
                indexAccum.push_back(vertexID + rowCount + 2);
                indexAccum.push_back(vertexID + rowCount + 1);
            } else lastRow = false;

			vertexID++;
		}
    }

    std::cout << "Vertex Count" << vertexID << std::endl;
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

    GL4_BumpGrid::vertexCount = vertexID;
    GL4_BumpGrid::feed[GL4_BumpGrid::EBO] = feedBuffers[0];
    GL4_BumpGrid::feed[GL4_BumpGrid::feedPos] = feedBuffers[1];
    GL4_BumpGrid::feed[GL4_BumpGrid::feedTexCoord] = feedBuffers[2];

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_BumpGrid::create_v2(GLfloat rise, GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount){
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
    std::vector<GLuint> mpointIndexAccum;

    GLuint vertexID = 0;
	GLuint indexID = 0;
    srand(time(NULL));

    for(GLfloat currentCol = -1 * (GLfloat)yDimension / 2; currentCol <= (GLfloat)yDimension / 2; currentCol += colSize){
        if(currentCol >= (yDimension / 2) - colSize) lastCol = true;
        for(GLfloat currentRow = -1 * (GLfloat)xDimension / 2; currentRow <= (GLfloat)xDimension / 2; currentRow += rowSize){
            posAccum.push_back(currentRow);
            posAccum.push_back(currentCol);
            posAccum.push_back(((static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX)) * rise) - rise / 2);

			if (vertexID % (rowCount * 2) < rowCount) uTex = 0.0;
			else uTex = 1.0;
            texCoordAccum.push_back(uTex);
			if (vertexID % 2 == 0) vTex = 0.0;
			else vTex = 1.0;
            texCoordAccum.push_back(vTex);
            
            if(currentRow >= (xDimension / 2) - rowSize) lastRow = true;

            if(! lastRow && ! lastCol){
                indexAccum.push_back(vertexID + 1);
                indexAccum.push_back(vertexID);
                indexAccum.push_back(vertexID + rowCount + 1);
                indexAccum.push_back(vertexID + 1);
                indexAccum.push_back(vertexID + rowCount + 2);
                indexAccum.push_back(vertexID + rowCount + 1);

                mpointIndexAccum.push_back(vertexID);
                mpointIndexAccum.push_back(vertexID + 1);
                mpointIndexAccum.push_back(vertexID + rowCount + 1);
                mpointIndexAccum.push_back(vertexID + rowCount + 2);
				indexID++;
            } else lastRow = false;
			vertexID++;
		}
    }
	std::cout << "Vertex ID: " << vertexID << std::endl;
    std::vector<GLfloat> mpointAccum;
	mpointAccum.push_back(0.0f);
	
    /* for(GLuint mpointIndexElem = 0; mpointIndexElem < indexID; mpointIndexElem++){
        float avrgX = ( posAccum[mpointIndexAccum[mpointIndexElem * 4] * 3] +
                        posAccum[mpointIndexAccum[mpointIndexElem * 4 + 1] * 3] +
                        posAccum[mpointIndexAccum[mpointIndexElem * 4 + 2] * 3] +
                        posAccum[mpointIndexAccum[mpointIndexElem * 4 + 3] * 3] ) / 4;
        float avrgY = ( posAccum[mpointIndexAccum[mpointIndexElem * 4] * 3 + 1] + 
                        posAccum[mpointIndexAccum[mpointIndexElem * 4 + 1] * 3 + 1] +
                        posAccum[mpointIndexAccum[mpointIndexElem * 4 + 2] * 3 + 1] +
                        posAccum[mpointIndexAccum[mpointIndexElem * 4 + 3] * 3 + 1] ) / 4;
        float avrgZ = ( posAccum[mpointIndexAccum[mpointIndexElem * 4] * 3 + 2] + 
                        posAccum[mpointIndexAccum[mpointIndexElem * 4 + 1] * 3 + 2] +
                        posAccum[mpointIndexAccum[mpointIndexElem * 4 + 2] * 3 + 2] +
                        posAccum[mpointIndexAccum[mpointIndexElem * 4 + 3] * 3 + 2] ) / 4;
        mpointAccum.push_back(avrgX);
        mpointAccum.push_back(avrgY);
        mpointAccum.push_back(avrgZ);
		std::cout << mpointIndexElem << " Element number" << std::endl;
    } */

    GLuint feedBuffers[5];
    glGenBuffers(5, feedBuffers);
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
	// SAVE FOR NORMALS
	/* * * * * * * * * * * * * * * * * * * * * * * * 
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[3]);
    glBufferData(GL_ARRAY_BUFFER, normalAccum.size() * sizeof(GLfloat), &normalAccum[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(2);
	* * * * * * * * * * * * * * * * * * * * * * * */
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[4]);
	glBufferData(GL_ARRAY_BUFFER, mpointAccum.size() * sizeof(GLfloat), &mpointAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(3);

    GL4_BumpGrid::vertexCount = vertexID;
    GL4_BumpGrid::feed[GL4_BumpGrid::EBO] = feedBuffers[0];
    GL4_BumpGrid::feed[GL4_BumpGrid::feedPos] = feedBuffers[1];
    GL4_BumpGrid::feed[GL4_BumpGrid::feedTexCoord] = feedBuffers[2];
	GL4_BumpGrid::feed[GL4_BumpGrid::feedNormal] = feedBuffers[3];
	GL4_BumpGrid::feed[GL4_BumpGrid::feedMidpoint] = feedBuffers[4];

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	indexAccum->resize(GL4_BumpGrid::vertexCount * 6);

    for(GLuint indexElem = 0; indexElem < indexAccum->size(); indexElem++){
		indexAccum->at(indexElem) = *(indexData + indexElem);
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
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