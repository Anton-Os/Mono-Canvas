#include "Loaders.h"

void GL4_BufferFeeder::init(GLuint buffFeedsCount){
    if (buffFeedsCount != GL4_BufferFeeder::bufferFeed.VBO.size())
        std::cerr << "When calling GL_BufferFeeder constructor arg 'buffFeedsCount' must match GL_BufferFeed VBO vector in size" << std::endl;
    else glGenBuffers(buffFeedsCount, &GL4_BufferFeeder::bufferFeed.VBO[0]);
}

void GL4_BufferFeed::cycle(){
    for(GLuint fb = 0; fb < GL4_BufferFeed::VBO.size(); fb++){
        glBindBuffer(GL4_BufferFeed::target[fb], GL4_BufferFeed::VBO[fb]);
        glBufferData(GL4_BufferFeed::target[fb], GL4_BufferFeed::size[fb], GL4_BufferFeed::data[fb], GL4_BufferFeed::usage[fb]);
    }
}

void GL4_VAttribFeed::cycle(){
    for(GLuint va = 0; va < GL4_VAttribFeed::VBO.size(); va++){
        glBindBuffer(GL_ARRAY_BUFFER, GL4_VAttribFeed::VBO[va]);
        glVertexAttribPointer(GL4_VAttribFeed::attribID[va], 
                              GL4_VAttribFeed::compCount[va], 
                              GL4_VAttribFeed::dataType[va],
                              GL4_VAttribFeed::isNrm[va], 
                              0, 
                              nullptr
        );
        glEnableVertexAttribArray(GL4_VAttribFeed::attribID[va]);
    }
}