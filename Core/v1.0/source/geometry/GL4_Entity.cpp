#include "Feeds.h"
#include "geometry/GL4_Entity.hpp"

void GL4_Entity_Feed::feed(GLuint VAO, GLsizei size, const void *data){
    glBindVertexArray(VAO);
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_Entity_Feed::buffer);

    glBufferData(GL_ARRAY_BUFFER, size, data, GL4_Entity_Feed::usage);
    glVertexAttribPointer(GL4_Entity_Feed::feedID, 
                          GL4_Entity_Feed::perVertex, 
                          GL4_Entity_Feed::type, 
                          GL4_Entity_Feed::normalized, 
                          GL4_Entity_Feed::stride, 
                          GL4_Entity_Feed::offset);
    glEnableVertexAttribArray(GL4_Entity_Feed::feedID);

    GL4_Entity_Feed::isFed = true;
    glBindVertexArray(0);
}

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

void GL4_Entity::dump(vertexFeed* vFeed){
    vFeed->perVertex = GL4_Entity::perVertex;
    vFeed->pos = GL4_Entity::mapPos();
}

void GL4_Entity::dump(vertexFeedIdx* vFeed){
    vFeed->perVertex = GL4_Entity::perVertex;
    vFeed->pos = GL4_Entity::mapPos();
    vFeed->idx = GL4_Entity::mapIdx();
}

void GL4_Entity::init(){
    GLuint VertexArray;
    GLuint buffers[2];

    glGenVertexArrays(1, &VertexArray);
    glBindVertexArray(VertexArray);

    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

    GL4_Entity::VAO = VertexArray;
    GL4_Entity::posBff = buffers[0];
    GL4_Entity::idxBff = buffers[1];
}

void GL4_Entity::feedPos(const void* data, GLuint vertexCount){
    glBindVertexArray(GL4_Entity::VAO);
    glBindBuffer(GL_ARRAY_BUFFER, GL4_Entity::posBff);

    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat), data, GL_STATIC_DRAW);
    glVertexAttribPointer(FEED_POS_ID, FEED_POS_COUNT, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(FEED_POS_ID);
    
    GL4_Entity::vertexCount = vertexCount / GL4_Entity::perVertex;
    GL4_Entity::isFed = true;
    glBindVertexArray(0);
}

void GL4_Entity::feedIdx(const void* data, GLuint indexCount){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL4_Entity::idxBff);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), data, GL_STATIC_DRAW);
    GL4_Entity::idxCount = indexCount;
    GL4_Entity::isIdx = true;
}

void GL4_Entity::clearPos(){
    glBindBuffer(GL_ARRAY_BUFFER, GL4_Entity::posBff);
    glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);
    glDisableVertexAttribArray(0);
    GL4_Entity::vertexCount = 0;
    GL4_Entity::isFed = false;
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