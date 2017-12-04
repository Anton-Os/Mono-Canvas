#include "geometry/GL4_PolyTraverse.hpp"

void GL4_PolyTraverse::reset(){
    GL4_PolyTraverse::trvBits.reset();
    GL4_PolyTraverse::indexCount = 0;
    GL4_PolyTraverse::vertexCount = 0;
    GL4_PolyTraverse::relMatrix = glm::mat4(1);
    GL4_PolyTraverse::traverse = nullptr;
    GL4_PolyTraverse::traverseIdx = nullptr;
}

/* void GL4_PolyTraverse::createXI(){
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, threePts.size() * sizeof(GLfloat), threePts.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    GL4_PolyTraverse::isFed = true;
    GL4_PolyTraverse::vertexCount = threePts.size() / 3;
    GL4_PolyTraverse::VAO = VAO;
    GL4_PolyTraverse::posBff = VBO;
} */

void GL4_PolyTraverse::map(std::vector<float>* posAccum){
    if(!GL4_PolyTraverse::isFed) {
        std::cerr << "Cannot perform an mapping on feedPos, invoke create()" << std::endl;
        return;
    }
    glBindVertexArray(GL4_PolyTraverse::VAO);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_PolyTraverse::posBff);
    GLfloat* posData = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
	posAccum->resize(GL4_PolyTraverse::vertexCount * 3);

    for(GLuint posElem = 0; posElem < posAccum->size(); posElem++){
		posAccum->at(posElem) = *(posData + posElem);
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(0);
}

void GL4_PolyTraverse::draw(GLenum drawMode){
    if(!GL4_PolyTraverse::isIdx) {
        std::cerr << "Cannot perform an indexed draw on non-indexed object" << std::endl;
        return;
    }
    glBindVertexArray(GL4_PolyTraverse::VAO);
    glDrawElements(drawMode, GL4_PolyTraverse::indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_PolyTraverse::draw(GLenum drawMode, unsigned int drawCount){
    if(!GL4_PolyTraverse::isIdx) {
        std::cerr << "Cannot perform an indexed draw on non-indexed object" << std::endl;
        return;
    }
    glBindVertexArray(GL4_PolyTraverse::VAO);
    if(drawCount > GL4_PolyTraverse::indexCount)
        glDrawElements(drawMode, GL4_PolyTraverse::indexCount, GL_UNSIGNED_INT, 0);
    else glDrawElements(drawMode, drawCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
