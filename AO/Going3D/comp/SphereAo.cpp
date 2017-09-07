#include "Common.h"
#include "Sphere.h"

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


int createSphere(ModelComposite* sphereModel, GLfloat radius, GLuint sliceCount, GLuint stackCount){
    GLfloat uTex = 0.0; GLfloat vTex = 0.0;
	GLuint sliceIt = 0; GLuint stackIt = 0; GLuint vertexID = 0;
    for(double phi = 0; phi < glm::pi<float>() * 2; phi += glm::pi<float>() / sliceCount){
        for(double theta = 0; theta < glm::pi<float>(); theta += glm::pi<float>() / stackCount){
            Point spherePoint;
            spherePoint.pos = { radius * (GLfloat)std::cos(phi) * (GLfloat)std::sin(theta),
                                radius * (GLfloat)std::sin(phi) * (GLfloat)std::sin(theta),
                                radius * (GLfloat)std::cos(theta) };
            spherePoint.color = {0.0, 0.0, 0.0, 0.0};
            spherePoint.normal = {0.0, 0.0, 0.0};
            spherePoint.texCoord = { uTex, vTex };
            sphereModel->modelMeshes.push_back(spherePoint);

            // DAVIDBITTON APPROACH
            /* GLint i1 = (sliceIt * (stackCount + 1)) + stackIt;
            GLint i2 = i1 + stackCount + 1;

            sphereModel->modelIndices.push_back(i1);
            sphereModel->modelIndices.push_back(i2);
            sphereModel->modelIndices.push_back(i1 + 1);
            sphereModel->modelIndices.push_back(i2);
            sphereModel->modelIndices.push_back(i2 + 1);
            sphereModel->modelIndices.push_back(i1 + 1); */
            
            // VERTEX ID APPROACH
            sphereModel->modelIndices.push_back(vertexID); // SHARED LOWER LEFT
            sphereModel->modelIndices.push_back(vertexID + 1);
            sphereModel->modelIndices.push_back(vertexID + stackCount + 1); // SHARED UPPER RIGHT
            sphereModel->modelIndices.push_back(vertexID);
            sphereModel->modelIndices.push_back(vertexID + stackCount);
            sphereModel->modelIndices.push_back(vertexID + stackCount + 1);

			vertexID++; stackIt++;
			// vTex += vTexInc;
        }
        sliceIt++;
		// stackIt = 0;
        //  uTex += uTexInc;
    }
    sphereModel->relativePos = glm::mat4(1);
    std::string sphereBits = "10110";
    sphereModel->VertexArray = loadModelData(sphereModel, std::bitset<5>(sphereBits));
    return 0;
}