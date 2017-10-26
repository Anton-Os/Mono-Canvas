#include "Geometry.h"

void GL4_RigidLine::create(GLfloat rise, GLuint segCount, GLfloat xLength, GLfloat xVariance){
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
        GL4_RigidLine::length += xLength + xRand;
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
	GL4_RigidLine::feed[GL4_RigidLine::VAO] = VAO;

    GLuint feedBuffers[2];
	glGenBuffers(2, feedBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, feedBuffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAccum.size() * sizeof(GLuint), &indexAccum[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, posAccum.size() * sizeof(GLfloat), &posAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

    GL4_RigidLine::vertexCount = vertexID;
	GL4_RigidLine::feed[GL4_RigidLine::EBO] = feedBuffers[0];
	GL4_RigidLine::feed[GL4_RigidLine::feedPos] = feedBuffers[1];

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_RigidLine::create(GLfloat rise, GLfloat thickness, GLuint segCount, GLfloat xLength, GLfloat xVariance){
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
        GL4_RigidLine::length += xLength + xRand;

        if(lineSegElem != segCount){
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
	GL4_RigidLine::feed[GL4_RigidLine::VAO] = VAO;

    GLuint feedBuffers[2];
	glGenBuffers(2, feedBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, feedBuffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAccum.size() * sizeof(GLuint), &indexAccum[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, feedBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, posAccum.size() * sizeof(GLfloat), &posAccum[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

    GL4_RigidLine::vertexCount = vertexID * 2;
	GL4_RigidLine::feed[GL4_RigidLine::EBO] = feedBuffers[0];
	GL4_RigidLine::feed[GL4_RigidLine::feedPos] = feedBuffers[1];

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_RigidLine::map(GLubyte feedLoc, std::vector<GLfloat>* fltAccum){
    glBindVertexArray(GL4_RigidLine::feed[GL4_RigidLine::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_RigidLine::feed[GL4_RigidLine::feedPos]);
    GLfloat* fltData = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
	fltAccum->resize(GL4_RigidLine::vertexCount * 3);

    for(GLuint fltElem = 0; fltElem < fltAccum->size(); fltElem++){
		fltAccum->at(fltElem) = *(fltData + fltElem);
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(0);
}

std::array<float, 4> GL4_RigidLine::get_endPoints(){
    std::vector<float> posAccum;
    GL4_RigidLine::map(GL4_RigidLine::feedPos, &posAccum);
    GLuint vertexCount = GL4_RigidLine::vertexCount;
    std::array<float, 4> endPoints = {posAccum[vertexCount], posAccum[vertexCount - 1], posAccum[vertexCount - 2], posAccum[vertexCount - 3]};
    return endPoints;
}

std::array<float, 4> GL4_RigidLine::get_startPoints(){
    std::vector<float> posAccum;
    GL4_RigidLine::map(GL4_RigidLine::feedPos, &posAccum);
    std::array<float, 4> startPoints = {posAccum[0], posAccum[1], posAccum[2], posAccum[3]};
    return startPoints;
}

void GL4_RigidLine::draw(){
    glBindVertexArray(GL4_RigidLine::feed[0]);
    glDrawElements(GL_POINTS, GL4_RigidLine::indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_RigidLine::draw(GLenum drawMode){
    glBindVertexArray(GL4_RigidLine::feed[0]);
    glDrawElements(drawMode, GL4_RigidLine::indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_RigidLine::drawFixed(GLenum drawMode, GLuint indexCount){
    glBindVertexArray(GL4_RigidLine::feed[0]);
    if(indexCount >= GL4_RigidLine::vertexCount * 6) glDrawElements(drawMode, GL4_RigidLine::indices, GL_UNSIGNED_INT, 0);
    else glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_RigidLine::drawXI(GLenum drawMode){
    glBindVertexArray(GL4_RigidLine::feed[0]);
    glDrawArrays(drawMode, 0, GL4_RigidLine::vertexCount);
    glBindVertexArray(0);
}

void GL4_RigidLine::drawXI(GLenum drawMode, GLuint indexCount){
    glBindVertexArray(GL4_RigidLine::feed[0]);
    if(indexCount >= GL4_RigidLine::vertexCount) glDrawArrays(drawMode, 0, GL4_RigidLine::vertexCount);
    else glDrawArrays(drawMode, 0, indexCount);
    glBindVertexArray(0);
}