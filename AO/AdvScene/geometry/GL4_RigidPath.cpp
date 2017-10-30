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

void GL4_RigidPath::extendLine(GLfloat rise, GLfloat thickness, GLuint segCount, GLfloat xLength, GLfloat xVariance){
    if(xVariance > xLength * 2){
        std::cerr << "xVariance cannot exceed xLength by a factor of 2" << std::endl;
        return;
    }
    srand(time(NULL));
    
    std::vector<GLfloat> posPrevAccum;
    GL4_RigidPath::map(GL4_RigidPath::feed[GL4_RigidPath::feedPos], &posPrevAccum);
    std::vector<GLuint> indexPrevAccum;
    GL4_RigidPath::map(GL4_RigidPath::feed[GL4_RigidPath::feedPos], &indexPrevAccum);

    std::vector<GLfloat> posAccum;
    std::vector<GLfloat> indexAccum;

    GLuint vertexID = 0;
    float xRand; float yRand;

    for(GLuint lineSegElem = 0; lineSegElem <= segCount; lineSegElem++){
        xRand = (static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX) * xVariance) - (xVariance / 2);
        yRand = (static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX) * rise) - (rise / 2);
        posAccum.push_back((xLength * lineSegElem) + xRand);
        posAccum.push_back(yRand - (thickness / 2));
        posAccum.push_back((xLength * lineSegElem) + xRand);
        posAccum.push_back(yRand + (thickness / 2));
        GL4_RigidPath::length += xLength + xRand;

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

    glBindVertexArray(GL4_RigidPath::feed[GL4_RigidPath::VAO]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL4_RigidPath::feed[GL4_RigidPath::EBO]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * (indexPrevAccum.size() + indexAccum.size()), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLuint) * indexPrevAccum.size(), &indexPrevAccum[0]);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indexPrevAccum.size(), sizeof(GLuint) * indexAccum.size(), &indexAccum[0]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_RigidPath::feed[GL4_RigidPath::feedPos]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (posPrevAccum.size() + posAccum.size()), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * posPrevAccum.size(), &posPrevAccum[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * posPrevAccum.size(), sizeof(GLuint) * posAccum.size(), &posAccum[0]);

    GL4_RigidPath::vertexCount += vertexID * 2;
    GL4_RigidPath::indices += indices;

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


std::array<float, 4> GL4_RigidPath::get_startPoints(){
    glBindVertexArray(GL4_RigidPath::feed[GL4_RigidPath::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_RigidPath::feed[GL4_RigidPath::feedPos]);
    GLfloat* fltData = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);

    std::array<float, 4> startPoints;
    startPoints = { *(fltData), *(fltData + 1), *(fltData + 2), *(fltData + 3) };

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(0);
    return startPoints;
}

std::array<float, 4> GL4_RigidPath::get_endPoints(){
    GLuint vertexCount = GL4_RigidPath::vertexCount;
	GLuint vAttribCount = 2;

    glBindVertexArray(GL4_RigidPath::feed[GL4_RigidPath::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_RigidPath::feed[GL4_RigidPath::feedPos]);
    GLfloat* fltData = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);

    std::array<float, 4> endPoints;
    endPoints = { *(fltData + ((vertexCount * vAttribCount) - 4)), *(fltData + ((vertexCount * vAttribCount) - 3)), *(fltData + ((vertexCount * vAttribCount) - 2)), *(fltData + ((vertexCount * vAttribCount) - 1)) };

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(0);
    return endPoints;
}

void GL4_RigidPath::set_startPoints(std::array<float, 4>* startPoints){
    glBindVertexArray(GL4_RigidPath::feed[GL4_RigidPath::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_RigidPath::feed[GL4_RigidPath::feedPos]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4, startPoints->data());
    return;
}

void GL4_RigidPath::set_endPoints(std::array<float, 4>* endPoints){
    GLuint vertexCount = GL4_RigidPath::vertexCount;
    GLuint vAttribCount = 2;
    glBindVertexArray(GL4_RigidPath::feed[GL4_RigidPath::VAO]);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_RigidPath::feed[GL4_RigidPath::feedPos]);
    glBufferSubData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * vertexCount * vAttribCount) - (sizeof(GLfloat) * 4), sizeof(GLfloat) * 4, endPoints->data());
    return;
}

void GL4_RigidPath::draw(){
    glBindVertexArray(GL4_RigidPath::feed[0]);
    glDrawElements(GL_POINTS, GL4_RigidPath::indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_RigidPath::draw(GLenum drawMode){
    glBindVertexArray(GL4_RigidPath::feed[0]);
    glDrawElements(drawMode, GL4_RigidPath::indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_RigidPath::drawFixed(GLenum drawMode, GLuint indexCount){
    glBindVertexArray(GL4_RigidPath::feed[0]);
    if(indexCount >= GL4_RigidPath::vertexCount * 6) glDrawElements(drawMode, GL4_RigidPath::indices, GL_UNSIGNED_INT, 0);
    else glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_RigidPath::drawXI(GLenum drawMode){
    glBindVertexArray(GL4_RigidPath::feed[0]);
    glDrawArrays(drawMode, 0, GL4_RigidPath::vertexCount);
    glBindVertexArray(0);
}

void GL4_RigidPath::drawXI(GLenum drawMode, GLuint indexCount){
    glBindVertexArray(GL4_RigidPath::feed[0]);
    if(indexCount >= GL4_RigidPath::vertexCount) glDrawArrays(drawMode, 0, GL4_RigidPath::vertexCount);
    else glDrawArrays(drawMode, 0, indexCount);
    glBindVertexArray(0);
}