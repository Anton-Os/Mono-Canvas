#include "Geometry.h"

void GL4_RigidPath::create(GLfloat rise, GLfloat thickness, GLuint segCount, GLfloat xLength){
    srand(time(NULL));
    
    std::vector<GLfloat> posAccum;
	std::vector<GLuint> indexAccum;

    GLuint vertexID = 0;
    float yRand;

    for(GLuint lineSegElem = 0; lineSegElem <= segCount; lineSegElem++){
        yRand = (static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX) * rise) - (rise / 2);
        posAccum.push_back(xLength * lineSegElem);
        posAccum.push_back(yRand - (thickness / 2));
        posAccum.push_back(xLength * lineSegElem);
        posAccum.push_back(yRand + (thickness / 2));
        GL4_RigidPath::length += xLength;

        vertexID++;
    }

    GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GL4_RigidPath::feed[GL4_RigidPath::VAO] = VAO;

    GLuint feedBuffers[2];
	glGenBuffers(2, feedBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, feedBuffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAccum.size() * sizeof(GLuint), &indexAccum[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, posAccum.size() * sizeof(GLfloat), &posAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

    GL4_RigidPath::vertexCount = vertexID * 2;
    GL4_RigidPath::length = posAccum[GL4_RigidPath::vertexCount - 2];
	GL4_RigidPath::feed[GL4_RigidPath::EBO] = feedBuffers[0];
	GL4_RigidPath::feed[GL4_RigidPath::feedPos] = feedBuffers[1];

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_RigidPath::create(GLfloat rise, GLfloat thickness, GLuint segCount, GLfloat xLength, GLfloat xVariance){
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
        // GL4_RigidPath::length += xLength + xRand;

        vertexID++;
    }

    GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GL4_RigidPath::feed[GL4_RigidPath::VAO] = VAO;

    GLuint feedBuffers[2];
	glGenBuffers(2, feedBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, feedBuffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAccum.size() * sizeof(GLuint), &indexAccum[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, posAccum.size() * sizeof(GLfloat), &posAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

    GL4_RigidPath::vertexCount = vertexID * 2;
    GL4_RigidPath::length = posAccum[GL4_RigidPath::vertexCount - 2];
	GL4_RigidPath::feed[GL4_RigidPath::EBO] = feedBuffers[0];
	GL4_RigidPath::feed[GL4_RigidPath::feedPos] = feedBuffers[1];

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_RigidPath::map(GLubyte feedLoc, std::vector<GLfloat>* fltAccum){
    glBindVertexArray(GL4_RigidPath::feed[GL4_RigidPath::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_RigidPath::feed[GL4_RigidPath::feedPos]);
    GLfloat* fltData = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
	fltAccum->resize(GL4_RigidPath::vertexCount * 2);

    for(GLuint fltElem = 0; fltElem < fltAccum->size(); fltElem++){
		fltAccum->at(fltElem) = *(fltData + fltElem);
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(0);
}

void GL4_RigidPath::map(GLubyte feedLoc, std::vector<GLuint>* uintAccum){
    glBindVertexArray(GL4_RigidPath::feed[GL4_RigidPath::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_RigidPath::feed[GL4_RigidPath::EBO]);
    GLuint* uintData = (GLuint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
	uintAccum->resize(GL4_RigidPath::vertexCount * 3);

    for(GLuint uintElem = 0; uintElem < uintAccum->size(); uintElem++){
		uintAccum->at(uintElem) = *(uintData + uintElem);
    }

    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBindVertexArray(0);
}

void GL4_RigidPath::draw(){
    glBindVertexArray(GL4_RigidPath::feed[0]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, GL4_RigidPath::vertexCount);
    glBindVertexArray(0);
}

void GL4_RigidPath::draw(GLenum drawMode){
    glBindVertexArray(GL4_RigidPath::feed[0]);
    glDrawArrays(drawMode, 0, GL4_RigidPath::vertexCount);
    glBindVertexArray(0);
}

void GL4_RigidPath::drawFixed(GLenum drawMode, GLuint indexCount){
    glBindVertexArray(GL4_RigidPath::feed[0]);
    if(indexCount >= GL4_RigidPath::vertexCount) glDrawArrays(drawMode, 0, GL4_RigidPath::vertexCount);
    else glDrawArrays(drawMode, 0, indexCount);
    glBindVertexArray(0);
}