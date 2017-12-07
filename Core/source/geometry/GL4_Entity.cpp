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