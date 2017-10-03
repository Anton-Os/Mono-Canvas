#include "Prototypes.h"

void GL4_Sphere::create(GLuint radius, GLuint sliceCount, GLuint stackCount){
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GL4_Sphere::feed.push_back(VAO);
    
    GLfloat uTex = 0.0; GLfloat vTex = 0.0;
    GLfloat uTexInc = 1 / (GLfloat)sliceCount; GLfloat vTexInc = 1 / (GLfloat)stackCount;
    GLuint vertexID = 0;

    std::vector<GLfloat> posAccum;
    std::vector<GLfloat> texCoordAccum;
    std::vector<GLuint> indexAccum;

    for(double phi = 0; phi < glm::pi<float>() * 2; phi += glm::pi<float>() / sliceCount){
        for(double theta = 0; theta < glm::pi<float>(); theta += glm::pi<float>() / stackCount){
            posAccum.push_back(radius * (GLfloat)std::cos(phi) * (GLfloat)std::sin(theta));
            posAccum.push_back(radius * (GLfloat)std::sin(phi) * (GLfloat)std::sin(theta));
            posAccum.push_back(radius * (GLfloat)std::cos(theta));

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

    /* GLuint vertexCount = sliceCount * stackCount;
    posAccum.resize(vertexCount * 3);
    texCoordAccum.resize(vertexCount * 2);
    indexAccum.resize(vertexCount * 6);

    for(double phi = 0; phi < glm::pi<float>() * 2; phi += glm::pi<float>() / sliceCount){
        for(double theta = 0; theta < glm::pi<float>(); theta += glm::pi<float>() / stackCount){
            posAccum[vertexID * 3] = radius * (GLfloat)std::cos(phi) * (GLfloat)std::sin(theta);
            posAccum[(vertexID * 3) + 1] = radius * (GLfloat)std::sin(phi) * (GLfloat)std::sin(theta);
            posAccum[(vertexID * 3) + 2] = radius * (GLfloat)std::cos(theta);

			if (vertexID % (stackCount * 2) < stackCount) uTex = 0.0;
			else uTex = 1.0;
            texCoordAccum[vertexID * 2] = uTex;
			if (vertexID % 2 == 0) vTex = 0.0;
			else vTex = 1.0;
            texCoordAccum[(vertexID * 2) + 1] = vTex;
            
            indexAccum[vertexID * 6] = vertexID;
            indexAccum[(vertexID * 6) + 1] = vertexID + 1;
            indexAccum[(vertexID * 6) + 2] = vertexID + stackCount + 1;
            indexAccum[(vertexID * 6) + 3] = vertexID;
            indexAccum[(vertexID * 6) + 4] = vertexID + stackCount;
            indexAccum[(vertexID * 6) + 5] = vertexID + stackCount + 1;

			vertexID++;
		}
    } */

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

    GL4_Sphere::feed.push_back(feedBuffers[0]);
    GL4_Sphere::feed.push_back(feedBuffers[1]);
    GL4_Sphere::feed.push_back(feedBuffers[2]);

    glBindVertexArray(0);
}

void GL4_Sphere::draw(){
    glBindVertexArray(GL4_Sphere::feed[0]);
    // glDrawElements(GL_TRIANGLES, );
    glBindVertexArray(0);
}