#include "Common.h"
#include "Sphere.h"

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#define GLM_ENABLE_EXPERIMENTAL

int createSphere(ModelComposite* sphereModel, GLfloat size, GLuint slices, GLuint stacks){
    GLfloat uTexInc = 1.0 / slices;
    GLfloat vTexInc = 1.0 / stacks;
    GLfloat uTex = 0.0;
    GLfloat vTex = 0.0;
    Point spherePoint;
    for(GLuint sl = 0; sl < slices; sl++){
        float pSlice = glm::pi<float>() * (-0.5 + (float) (sl - 1) / slices);
        float pSliceOpp = std::sin(pSlice);
        float pSliceAdj = std::cos(pSlice);

        /* float cSlice = glm::pi<float>() * (-0.5 + (float) sl / slices);
        float cSliceOpp = std::sin(cSlice);
        float cSliceAdj = std::cos(cSlice); */
        for(GLuint st = 0; st < stacks; st++){
            float pStack = 2 * glm::pi<float>() * (float) (st - 1) / stacks;
            float pStackOpp = std::cos(pStack);
            float pStackAdj = std::sin(pStack);
            spherePoint.pos = { pStackAdj * pSliceAdj * size, pStackOpp * pSliceAdj * size, pSliceOpp * size };
            spherePoint.color = genRandomColors(0.5); // marked for removal
            spherePoint.normal = {0.0, 0.0, 0.0}; // marked for removal
            spherePoint.texCoord = { uTex, vTex };
            sphereModel->modelMeshes.push_back(spherePoint);
            vTex += vTexInc;
        }
        uTex += uTexInc;
    }
    sphereModel->relativePos = glm::mat4(1);
    std::string sphereBits = "00110";
    sphereModel->VertexArray = loadModelData(sphereModel, std::bitset<5>(sphereBits));
    return 0;
}