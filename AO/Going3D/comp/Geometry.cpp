#include "Common.h"

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#define GLM_ENABLE_EXPERIMENTAL

unsigned int createRevLine(GLuint length, std::array<GLfloat, 2> pos, std::array<GLfloat, 2> change, std::array<GLfloat, 6> colorRange){
	std::vector<std::array<GLfloat, 3>> linePoint;
    std::vector<std::array<GLfloat, 3>> colorGrad;
    GLuint linePointID = 0;
	while(linePointID <= length){
		std::array<GLfloat, 3> currentPoint = {
            std::sin(pos[0]),
            std::sin(pos[1]), 
            std::cos(pos[0] + pos[1])
        };
		linePoint.push_back(currentPoint);
        pos[0] += change[0];
        pos[1] -= change[0];
        std::array<GLfloat, 3> currentColor = {
            (((colorRange[3] - colorRange[0]) / length) * linePointID) + colorRange[0],
            (((colorRange[4] - colorRange[1]) / length) * linePointID) + colorRange[1],
            (((colorRange[5] - colorRange[2]) / length) * linePointID) + colorRange[2],
        };
        colorGrad.push_back(currentColor);
		linePointID++;
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GLuint VBO[2];
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, linePoint.size() * sizeof(std::array<GLfloat, 3>), &linePoint[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, colorGrad.size() * sizeof(std::array<GLfloat, 3>), &colorGrad[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    return VAO;
}

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
    return 0;
}
