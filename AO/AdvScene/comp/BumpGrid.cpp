
#include "CompositeGeo.h"

/* void GL4_BumpGrid::create(GLfloat smoothness, GLuint xDimension, GLuint stackCount, GLuint yDimension, GLuint sliceCount){
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GL4_BumpGrid::feed[GL4_BumpGrid::VAO] = VAO;
    
    GLfloat sliceSize = (GLfloat)yDimension / (GLfloat)sliceCount;
    GLfloat stackSize = (GLfloat)xDimension / (GLfloat)stackCount;
    
    GL4_BumpGrid::vertexCount = stackCount * sliceCount;
    std::vector<GLuint> indexAccum(GL4_BumpGrid::vertexCount * 6);
    std::vector<GLfloat> posAccum(GL4_BumpGrid::vertexCount * 3);
    std::vector<GLfloat> texCoordAccum(GL4_BumpGrid::vertexCount * 2);
    std::vector<GLfloat> normalAccum(GL4_BumpGrid::vertexCount * 3);

    srand(time(NULL));
    GLuint vertexID = 0;
    for(GLfloat currentSlice = -1 * (GLfloat)yDimension / 2; currentSlice < (GLfloat)yDimension / 2; currentSlice += sliceSize){
        for(GLfloat currentStack = -1 * (GLfloat)xDimension / 2; currentStack < (GLfloat)xDimension / 2; currentStack += stackSize){
            GLfloat rise = (static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX)) * smoothness;
            posAccum[vertexID * 3] = currentStack;
            posAccum[vertexID * 3 + 1] = currentSlice;
            posAccum[vertexID * 3 + 2] = rise;
            std::cout << posAccum[vertexID * 3] << " " << posAccum[vertexID * 3 + 1] << " " << posAccum[vertexID * 3 + 2] << std::endl;
            
            if (vertexID % (stackCount * 2) < stackCount) texCoordAccum[vertexID * 2] = 0.0;
			else texCoordAccum[vertexID * 2] = 1.0;
			if (vertexID % 2 == 0) texCoordAccum[vertexID * 2 + 1] = 0.0;
			else texCoordAccum[vertexID * 2 + 1] = 1.0;

            indexAccum[vertexID * 6] = vertexID;
            indexAccum[vertexID * 6 + 1] = vertexID + 1;
            indexAccum[vertexID * 6 + 2] = vertexID + stackCount;
            indexAccum[vertexID * 6 + 3] = vertexID;
            indexAccum[vertexID * 6 + 4] = vertexID + stackCount + 1;
            indexAccum[vertexID * 6 + 5] = vertexID + stackCount;

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

void GL4_BumpGrid::create(GLfloat smoothness, GLuint xDimension, GLuint stackCount, GLuint yDimension, GLuint sliceCount){
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GL4_BumpGrid::feed[GL4_BumpGrid::VAO] = VAO;
    
    GLfloat uTex = 0.0; GLfloat vTex = 0.0;
    GLfloat sliceSize = (GLfloat)yDimension / (GLfloat)sliceCount;
    GLfloat stackSize = (GLfloat)xDimension / (GLfloat)stackCount;

    std::vector<GLfloat> posAccum;
    std::vector<GLfloat> texCoordAccum;
    std::vector<GLuint> indexAccum;

    GLuint vertexID = 0;
    srand(time(NULL));

    // boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();
    for(GLfloat currentSlice = -1 * (GLfloat)yDimension / 2; currentSlice < (GLfloat)yDimension / 2; currentSlice += sliceSize){
        for(GLfloat currentStack = -1 * (GLfloat)xDimension / 2; currentStack < (GLfloat)xDimension / 2; currentStack += stackSize){
            posAccum.push_back(currentStack);
            posAccum.push_back(currentSlice);
            posAccum.push_back((static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX)) * smoothness);

			if (vertexID % (stackCount * 2) < stackCount) uTex = 0.0;
			else uTex = 1.0;
            texCoordAccum.push_back(uTex);
			if (vertexID % 2 == 0) vTex = 0.0;
			else vTex = 1.0;
            texCoordAccum.push_back(vTex);
            
            indexAccum.push_back(vertexID);
            indexAccum.push_back(vertexID + 1);
            indexAccum.push_back(vertexID + stackCount + 1);
            indexAccum.push_back(vertexID);
            indexAccum.push_back(vertexID + stackCount);
            indexAccum.push_back(vertexID + stackCount + 1);

			vertexID++;
		}
    }

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