#include "Geometry.h"

void GL4_BumpLine::create(GLfloat rise, GLuint segCount, GLfloat xLength, GLfloat xVariance){
    if(xVariance > xLength * 2){
        std::cerr << "xVariance cannot exceed xLength by a factor of 2" << std::endl;
        return;
    }
    srand(time(NULL));
    
    std::vector<GLfloat> posAccum;
	std::vector<GLuint> indexAccum;

    GLuint vertexID = 0;
    float xRand; float yRand;

    for(GLuint lineSegElem = 0; lineSegElem <= segCount; lineSegElem++){
        xRand = (static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX) * xVariance) - (xVariance / 2);
        posAccum.push_back((xLength * lineSegElem) + xRand);
        GL4_BumpLine::length += xLength + xRand;
        posAccum.push_back((static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX) * rise) - (rise / 2));

        if(lineSegElem != segCount){
            indexAccum.push_back(vertexID);
            indexAccum.push_back(vertexID + 1);
            
            indices += 2;
        }

        vertexID++;
    }

    GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GL4_BumpLine::feed[GL4_BumpLine::VAO] = VAO;

    GLuint feedBuffers[2];
	glGenBuffers(2, feedBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, feedBuffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAccum.size() * sizeof(GLuint), &indexAccum[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, posAccum.size() * sizeof(GLfloat), &posAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

    GL4_BumpLine::vertexCount = vertexID;
	GL4_BumpLine::feed[GL4_BumpLine::EBO] = feedBuffers[0];
	GL4_BumpLine::feed[GL4_BumpLine::feedPos] = feedBuffers[1];

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_BumpLine::create(GLfloat rise, GLfloat thickness, GLuint segCount, GLfloat xLength, GLfloat xVariance){
    if(xVariance > xLength * 2){
        std::cerr << "xVariance cannot exceed xLength by a factor of 2" << std::endl;
        return;
    }
    srand(time(NULL));
    
    std::vector<GLfloat> posAccum;
	std::vector<GLuint> indexAccum;

    GLuint vertexID = 0;
    float xRand; float yRand;

    for(GLuint lineSegElem = 0; lineSegElem <= segCount; lineSegElem++){
        xRand = (static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX) * xVariance) - (xVariance / 2);
        yRand = (static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX) * rise) - (rise / 2);
        posAccum.push_back((xLength * lineSegElem) + xRand);
        posAccum.push_back(yRand - (thickness / 2));
        posAccum.push_back((xLength * lineSegElem) + xRand);
        posAccum.push_back(yRand + (thickness / 2));
        GL4_BumpLine::length += xLength + xRand;

        if(lineSegElem < segCount){
            indexAccum.push_back(vertexID * 4);
            indexAccum.push_back(vertexID * 4 + 1);
            indexAccum.push_back(vertexID * 4 + 2);
            indexAccum.push_back(vertexID * 4 + 1);
            indexAccum.push_back(vertexID * 4 + 3);
            indexAccum.push_back(vertexID * 4 + 2);

            indices += 6;
        }

        vertexID++;
    }

    GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GL4_BumpLine::feed[GL4_BumpLine::VAO] = VAO;

    GLuint feedBuffers[2];
	glGenBuffers(2, feedBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, feedBuffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAccum.size() * sizeof(GLuint), &indexAccum[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, posAccum.size() * sizeof(GLfloat), &posAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

    GL4_BumpLine::vertexCount = vertexID;
	GL4_BumpLine::feed[GL4_BumpLine::EBO] = feedBuffers[0];
	GL4_BumpLine::feed[GL4_BumpLine::feedPos] = feedBuffers[1];

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_BumpLine::draw(){
    glBindVertexArray(GL4_BumpLine::feed[0]);
    glDrawElements(GL_POINTS, GL4_BumpLine::vertexCount * GL4_BumpLine::indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_BumpLine::draw(GLenum drawMode){
    glBindVertexArray(GL4_BumpLine::feed[0]);
    glDrawElements(drawMode, GL4_BumpLine::vertexCount * GL4_BumpLine::indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}