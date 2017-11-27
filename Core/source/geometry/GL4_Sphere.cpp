#include "geometry/GL4_Sphere.hpp"

void GL4_Sphere::create(GLuint radius, GLuint sliceCount, GLuint stackCount){
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GL4_Sphere::feed[GL4_Sphere::VAO] = VAO;
    
    GLfloat uTex = 0.0; GLfloat vTex = 0.0;
    GLfloat uTexInc = 1 / (GLfloat)sliceCount; GLfloat vTexInc = 1 / (GLfloat)stackCount;
    GLuint vertexID = 0;

    std::vector<GLfloat> posAccum;
    std::vector<GLfloat> texCoordAccum;
    std::vector<GLuint> indexAccum;

    GLuint stackIt = 0; GLuint sliceIt = 0;

    // boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();
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

    GL4_Sphere::vertexCount = vertexID;
    GL4_Sphere::feed[GL4_Sphere::EBO] = feedBuffers[0];
    GL4_Sphere::feed[GL4_Sphere::feedPos] = feedBuffers[1];
    GL4_Sphere::feed[GL4_Sphere::feedTexCoord] = feedBuffers[2];

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL4_Sphere::draw(){
    glBindVertexArray(GL4_Sphere::feed[0]);
    glDrawElements(GL_TRIANGLES, GL4_Sphere::vertexCount * 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_Sphere::draw(GLenum drawMode){
    glBindVertexArray(GL4_Sphere::feed[0]);
    glDrawElements(drawMode, GL4_Sphere::vertexCount * 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_Sphere::drawFixed(GLenum drawMode, GLuint indexCount){
    glBindVertexArray(GL4_Sphere::feed[0]);
    if(indexCount > GL4_Sphere::vertexCount * 6) glDrawElements(drawMode, GL4_Sphere::vertexCount * 6, GL_UNSIGNED_INT, 0);
    else glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_Sphere::drawPart(GLenum drawMode, GLuint part, GLuint whole){
    GLuint indexCount = ((GLfloat)(GL4_Sphere::vertexCount * 6) / whole) * part;
    glBindVertexArray(GL4_Sphere::feed[0]);
    if(part >= whole) glDrawElements(drawMode, GL4_Sphere::vertexCount * 6, GL_UNSIGNED_INT, 0);
    else glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}