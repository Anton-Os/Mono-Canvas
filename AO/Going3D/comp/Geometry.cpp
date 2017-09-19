#include "Common.h"

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#define GLM_ENABLE_EXPERIMENTAL

unsigned int createRevLine(GLuint length, std::array<GLfloat, 2> posInit, std::array<GLfloat, 2> posChange){
    std::vector<std::array<GLfloat, 3>> lineSeg;
    for(GLuint linePt = 0; linePt < length; linePt++){
        std::array<GLfloat, 3> currentPt = {0.0, 0.0, 0.0};
        lineSeg.push_back(currentPt); 
    }
    // OpenGL buffer loading
    return 0;
}

void createSphere(ModelComposite* sphereModel, GLfloat radius, GLuint sliceCount, GLuint stackCount){
    GLfloat uTex = 0.0; GLfloat vTex = 0.0;
    GLfloat uTexInc = 1 / (GLfloat)sliceCount; GLfloat vTexInc = 1 / (GLfloat)stackCount;
    GLuint vertexID = 0;
    Point spherePoint;
    for(double phi = 0; phi < glm::pi<float>() * 2; phi += glm::pi<float>() / sliceCount){
        for(double theta = 0; theta < glm::pi<float>(); theta += glm::pi<float>() / stackCount){
            spherePoint.pos = { radius * (GLfloat)std::cos(phi) * (GLfloat)std::sin(theta),
                                radius * (GLfloat)std::sin(phi) * (GLfloat)std::sin(theta),
                                radius * (GLfloat)std::cos(theta) };
            spherePoint.color = {0.0, 0.0, 0.0, 0.0};
            spherePoint.normal = {0.0, 0.0, 0.0};
			if (vertexID % (stackCount * 2) < stackCount) uTex = 0.0;
			else uTex = 1.0;
			if (vertexID % 2 == 0) vTex = 0.0;
			else vTex = 1.0;
            spherePoint.texCoord = { uTex, vTex };
            sphereModel->modelMeshes.push_back(spherePoint);
            
            sphereModel->modelIndices.push_back(vertexID); // SHARED LOWER LEFT
            sphereModel->modelIndices.push_back(vertexID + 1);
            sphereModel->modelIndices.push_back(vertexID + stackCount + 1); // SHARED UPPER RIGHT
            sphereModel->modelIndices.push_back(vertexID);
            sphereModel->modelIndices.push_back(vertexID + stackCount);
            sphereModel->modelIndices.push_back(vertexID + stackCount + 1);

			vertexID++;
			// vTex += vTexInc;
        }
        // uTex += uTexInc;
    }
    
    sphereModel->relativePos = glm::mat4(1);
    std::string sphereBits = "10110";
	sphereModel->renderParams = std::bitset<5>(sphereBits);
    sphereModel->VertexArray = loadModelData(sphereModel);
}
