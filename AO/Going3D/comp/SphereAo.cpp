#include "Common.h"

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#define GLM_ENABLE_EXPERIMENTAL

int createSphere(ModelComposite* sphereModel, GLfloat radius, GLuint sliceCount, GLuint stackCount){
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
            spherePoint.texCoord = { uTex, vTex };
            sphereModel->modelMeshes.push_back(spherePoint);
            
            sphereModel->modelIndices.push_back(vertexID); // SHARED LOWER LEFT
            sphereModel->modelIndices.push_back(vertexID + 1);
            sphereModel->modelIndices.push_back(vertexID + stackCount + 1); // SHARED UPPER RIGHT
            sphereModel->modelIndices.push_back(vertexID);
            sphereModel->modelIndices.push_back(vertexID + stackCount);
            sphereModel->modelIndices.push_back(vertexID + stackCount + 1);

			vertexID++;
			vTex += vTexInc;
        }
        uTex += uTexInc;
    }
    
    sphereModel->relativePos = glm::mat4(1);
    std::string sphereBits = "10110";
	sphereModel->renderParams = std::bitset<5>(sphereBits);
    sphereModel->VertexArray = loadModelData(sphereModel);
    return 0;
}
