#include "Common.h"
#include "Sphere.h"

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#define GLM_ENABLE_EXPERIMENTAL

int createSphere(ModelComposite* sphereModel, GLfloat radius, GLuint slices, GLuint stacks){
    GLfloat uTexInc = 1.0 / slices;
    GLfloat vTexInc = 1.0 / stacks;
    GLfloat uTex, vTex = 0.0;
    Point spherePoint;
    for(GLuint sl = 0; sl < slices; sl++){
        for(GLuint st = 0; st < stacks; st++){
            spherePoint.texCoord = { uTex, vTex };
            sphereModel->modelMeshes.push_back(spherePoint);
            vTex += vTexInc;
        }
        uTex += uTexInc;
    }
    sphereModel->VertexArray = loadModelData(sphereModel);
    return 0;
}