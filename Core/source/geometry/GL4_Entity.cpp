#include "geometry/GL4_Entity.hpp"

void GL4_Entity::drawXI(GLenum drawMode){
    glBindVertexArray(GL4_Entity::VAO);
    glDrawArrays(drawMode, 0, GL4_Entity::vertexCount);
    glBindVertexArray(0);
}

void GL4_Entity::drawFixedXI(GLenum drawMode, GLuint drawCount){
    glBindVertexArray(GL4_Entity::VAO);
    if(drawCount > GL4_Entity::vertexCount) glDrawArrays(drawMode, 0, GL4_Entity::vertexCount);
    else glDrawArrays(drawMode, 0, drawCount);
    glBindVertexArray(0);
}

void GL4_Entity::drawPartXI(GLenum drawMode, GLuint part, GLuint whole){
    glBindVertexArray(GL4_Entity::VAO);
    if(part > whole) glDrawArrays(drawMode, 0, GL4_Entity::vertexCount);
    else glDrawArrays(drawMode, 0, GL4_Entity::vertexCount / whole * part);
    glBindVertexArray(0);
}

void GL4_Entity::draw(GLenum drawMode){
    if(!GL4_Entity::isIdx) {
        std::cerr << "Cannot perform an indexed draw on non-indexed object" << std::endl;
        return;
    }
    glBindVertexArray(GL4_Entity::VAO);
    glDrawElements(drawMode, GL4_Entity::idxCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_Entity::drawFixed(GLenum drawMode, unsigned int drawCount){
    if(!GL4_Entity::isIdx) {
        std::cerr << "Cannot perform an indexed draw on non-indexed object" << std::endl;
        return;
    }
    glBindVertexArray(GL4_Entity::VAO);
    if(drawCount > GL4_Entity::idxCount)
        glDrawElements(drawMode, GL4_Entity::idxCount, GL_UNSIGNED_INT, 0);
    else glDrawElements(drawMode, drawCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_Entity::drawPart(GLenum drawMode, GLuint part, GLuint whole){
    if(!GL4_Entity::isIdx) {
        std::cerr << "Cannot perform an indexed draw on non-indexed object" << std::endl;
        return;
    }
    glBindVertexArray(GL4_Entity::VAO);
    if(part > whole)
        glDrawElements(drawMode, GL4_Entity::idxCount, GL_UNSIGNED_INT, 0);
    else glDrawElements(drawMode, GL4_Entity::idxCount / whole * part, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}   

void GL4_Entity::feed(vertexFeed* vFeed){
    vFeed->pos = GL4_Entity::mapPos();
}

void GL4_Entity::feed(vertexFeedIdx* vFeed){
    vFeed->pos = GL4_Entity::mapPos();
    vFeed->idx = GL4_Entity::mapIdx();
}

std::vector<GLfloat> GL4_Entity::mapPos(){
    glBindVertexArray(GL4_Entity::VAO);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_Entity::posBff);
    GLfloat* posData = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);

    std::vector<GLfloat> posAccum;
    posAccum.resize(GL4_Entity::vertexCount * GL4_Entity::perVertex);

    for(GLuint posElem = 0; posElem < posAccum.size(); posElem++)
		posAccum[posElem] = *(posData + posElem);

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindVertexArray(0);

    return posAccum;
}

std::vector<GLuint> GL4_Entity::mapIdx(){
    glBindVertexArray(GL4_Entity::VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL4_Entity::idxBff);
    GLuint* idxData = (GLuint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);

    std::vector<GLuint> idxAccum;
    idxAccum.resize(GL4_Entity::idxCount);

    for(GLuint idxElem = 0; idxElem < idxAccum.size(); idxElem++)
		idxAccum[idxElem] = *(idxData + idxElem);

    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    glBindVertexArray(0);

    return idxAccum;
}
