#include "Common.h"
#include "Model3D.h"

GLuint processOpenGL(AssimpComposite* ModelComponent){
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(MeshBlock) * ModelComponent->modelMeshes.size(),
        &ModelComponent->modelMeshes.front(), 
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshBlock), (GLvoid*)offsetof(MeshBlock, pos));
    if(ModelComponent->renderParams[ImportCtrl::color])
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(MeshBlock), (GLvoid*)offsetof(MeshBlock, color));
    if(ModelComponent->renderParams[ImportCtrl::texCoord])
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshBlock), (GLvoid*)offsetof(MeshBlock, texCoord));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshBlock), (GLvoid*)offsetof(MeshBlock, normal));

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLuint) * ModelComponent->faceIndex.size(),
        &ModelComponent->faceIndex.front(),
        GL_STATIC_DRAW
    );

    GLenum errorLog = glGetError();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return VAO;
}

void CrossContext::processData(){
    for(unsigned int mi = 0; mi < CrossContext::MPerComponent->size(); mi++){
        if(CrossContext::MPerComponent->at(mi).renderParams[ImportCtrl::drawable]){
            GLuint VAO = processOpenGL(&CrossContext::MPerComponent->at(mi));
            CrossContext::vertexArray.push_back(VAO);
        }
    }
    return;
}

void CrossContext::draw(){
    for(unsigned int dr = 0; dr < CrossContext::MPerComponent->size(); dr++){
        if(CrossContext::MPerComponent->at(dr).renderParams[ImportCtrl::drawable]){
            glBindVertexArray(CrossContext::vertexArray.at(dr));
            glDrawElements(GL_TRIANGLES, MPerComponent->at(dr).faceIndex.size(), GL_UNSIGNED_INT, 0);
        }
    }
    return;
}