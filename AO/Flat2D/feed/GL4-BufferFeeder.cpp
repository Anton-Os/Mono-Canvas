#include "Loaders.h"

void GL4_BufferFeed::init(GLuint buffFeedsCount) {
    GL4_BufferFeed::VBO.resize(buffFeedsCount);
    GL4_BufferFeed::name.resize(buffFeedsCount);
    GL4_BufferFeed::target.resize(buffFeedsCount);
    GL4_BufferFeed:usage.resize(buffFeedsCount);
    GL4_BufferFeed::size.resize(buffFeedsCount);
    GL4_BufferFeed::data.resize(buffFeedsCount);
}

void GL4_BufferFeed::cycle(){
    for(GLuint fb = 0; fb < GL4_BufferFeed::VBO.size(); fb++){
        glBindBuffer(GL4_BufferFeed::target[fb], GL4_BufferFeed::VBO[fb]);
        glBufferData(GL4_BufferFeed::target[fb], GL4_BufferFeed::size[fb], GL4_BufferFeed::data[fb], GL4_BufferFeed::usage[fb]);
    }
}

void GL4_VAttribFeed::init(GLuint vAttribCount){
    GL4_VAttribFeed::VBO.resize(vAttribCount);
    GL4_VAttribFeed::attribID.resize(vAttribCount);
    GL4_VAttribFeed::compCount.resize(vAttribCount);
    GL4_VAttribFeed::dataType.resize(vAttribCount);
    GL4_VAttribFeed::isNrm.resize(vAttribCount);
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