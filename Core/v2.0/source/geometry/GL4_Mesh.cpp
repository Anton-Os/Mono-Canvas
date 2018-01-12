#include "geometry/GL4_Mesh.hpp"
#include "scene/ErrorCode.hpp"

void GL4_Mesh_Quill::init(GLboolean* fed, GLboolean* idx, GLuint* o, GLuint* v, GLuint* i){
    if(initPhase) logError(__FILE__, __LINE__, error_initPhase);
    
    if(nullptr == fed || nullptr == idx || nullptr == o || nullptr == v || nullptr == i)
        logError(__FILE__, __LINE__, error_nullPtrArgs);

    isFedPtr = fed;
    isIdxPtr = idx;
    vaoPtr = o;
    vertexCountPtr = v;
    indexCountPtr = i;
    initPhase = true;
}

void GL4_Mesh_Quill::unordered_draw(){
    if(! *isFedPtr) logError(__FILE__, __LINE__, error_drawNotFed);

    glBindVertexArray(*vaoPtr);
    glDrawArrays(mode, 0, *vertexCountPtr);
    glBindVertexArray(0);
}

void GL4_Mesh_Quill::ordered_draw(){
    if(! *isFedPtr) logError(__FILE__, __LINE__, error_drawNotFed);
    if(*isIdxPtr) logError(__FILE__, __LINE__, error_drawNotIdx);
    
    glBindVertexArray(*vaoPtr);
    glDrawArrays(mode, 0, *vertexCountPtr);
    glBindVertexArray(0);
}

void GL4_Mesh::init(){
    if(vertices.empty()) logError(__FILE__, __LINE__, error_drawNotFed);

    glGenVertexArrays(1, &VAO);

    std::vector<GLuint> buffers;
    buffers.resize(vertices.size());
    glGenBuffers(vertices.size(), buffers.data());

    for(unsigned v = 0; v < vertices.size(); v++) vertices[v].buffer = buffers[v];
    initPhase = true;
}

void GL4_Mesh::add_feed(GL4_Mesh_VertexFeed* vertexFeed){
    if(initPhase) logError(__FILE__, __LINE__, error_initPhase);

    vertices.push_back(*vertexFeed);
    feedCounter++;
}

void GL4_Mesh::del_feed(GLuint vAttrib){
    GLuint savedAttrib;
    GLboolean attribFound = false;
    for(unsigned v = 0; v < vertices.size(); v++){
        if(vertices[v].feedID == vAttrib){
            savedAttrib = v;
            attribFound = true;
            break;
        }
    }

    if(!attribFound) logError(__FILE__, __LINE__, error_elemNotFound);

    glDeleteBuffers(1, &vertices[savedAttrib].buffer);

    glBindVertexArray(VAO);
    glDisableVertexAttribArray(vAttrib);
    glBindVertexArray(0);
}

void GL4_Mesh::feed(GLuint vAttrib, const void * data, size_t size){
    if(!initPhase) init();

    GLuint savedAttrib;
    GLboolean attribFound = false;
    for(unsigned v = 0; v < vertices.size(); v++){
        if(vertices[v].feedID == vAttrib){
            savedAttrib = v;
            attribFound = true;
            break;
        }
    }

    if(!attribFound) logError(__FILE__, __LINE__, error_elemNotFound);

    glBindBuffer(vertices[savedAttrib].target, vertices[savedAttrib].buffer);
    glBufferData(vertices[savedAttrib].target, size * vertexCount, data, vertices[savedAttrib].usage);

    glBindVertexArray(VAO);
    if(vertices[savedAttrib].vaoPtrMode == vaoPtrModes::Default)
        glVertexAttribPointer(vertices[savedAttrib].feedID, vertices[savedAttrib].count, vertices[savedAttrib].type, vertices[savedAttrib].normalized, 0, nullptr);
    else if(vertices[savedAttrib].vaoPtrMode == vaoPtrModes::Integral)
        glVertexAttribIPointer(vertices[savedAttrib].feedID, vertices[savedAttrib].count, vertices[savedAttrib].type, 0, nullptr);
    else if(vertices[savedAttrib].vaoPtrMode == vaoPtrModes::Integral)
        glVertexAttribIPointer(vertices[savedAttrib].feedID, vertices[savedAttrib].count, vertices[savedAttrib].type, 0, nullptr);

    glEnableVertexAttribArray(vertices[savedAttrib].feedID);
    glBindVertexArray(0);

    if(!vertices[savedAttrib].isFed){
        vertices[savedAttrib].isFed = true;
        feedCounter--;
        if(feedCounter == 0) isFed = true;
    }
}