#include "geometry/GL4_Mesh.hpp"
#include "scene/ErrorCode.hpp"

void GL4_Mesh_Quill::init(const GLboolean* fed, const GLboolean* idx, const GLuint* o, const GLuint* v, const GLuint* i){
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
    if(feeds.empty()) logError(__FILE__, __LINE__, error_drawNotFed);

    glGenVertexArrays(1, &VAO);

    std::vector<GLuint> buffers;
    buffers.resize(feeds.size());
    glGenBuffers(feeds.size(), buffers.data());

    for(unsigned v = 0; v < feeds.size(); v++) feeds[v].buffer = buffers[v];
    initPhase = true;
}

void GL4_Mesh::add_feed(GL4_Vertex* vertexFeed){
    if(initPhase) logError(__FILE__, __LINE__, error_initPhase);

    feeds.push_back(*vertexFeed);
    feedCounter++;
}

void GL4_Mesh::del_feed(GLuint vAttrib){
    GLint savedAttrib = match_vAttrib(vAttrib, &feeds);
    if(savedAttrib < 0) logError(__FILE__, __LINE__, error_elemNotFound);

    glDeleteBuffers(1, &feeds[savedAttrib].buffer);

    glBindVertexArray(VAO);
    glDisableVertexAttribArray(vAttrib);
    glBindVertexArray(0);
}

void GL4_Mesh::run_feed(GLuint vAttrib, const void * data, size_t size){
    if(!initPhase) init();

    GLint savedAttrib = match_vAttrib(vAttrib, &feeds);
    if(savedAttrib < 0) logError(__FILE__, __LINE__, error_elemNotFound);

    glBindBuffer(feeds[savedAttrib].target, feeds[savedAttrib].buffer);
    glBufferData(feeds[savedAttrib].target, size * feeds[savedAttrib].count * vertexCount, data, feeds[savedAttrib].usage);

    glBindVertexArray(VAO);
    if(feeds[savedAttrib].vaoPtrMode == vaoPtrModes::Default)
        glVertexAttribPointer(feeds[savedAttrib].feedID, feeds[savedAttrib].count, feeds[savedAttrib].type, feeds[savedAttrib].normalized, 0, nullptr);
    else if(feeds[savedAttrib].vaoPtrMode == vaoPtrModes::Integral)
        glVertexAttribIPointer(feeds[savedAttrib].feedID, feeds[savedAttrib].count, feeds[savedAttrib].type, 0, nullptr);
    else if(feeds[savedAttrib].vaoPtrMode == vaoPtrModes::Integral)
        glVertexAttribIPointer(feeds[savedAttrib].feedID, feeds[savedAttrib].count, feeds[savedAttrib].type, 0, nullptr);

    glEnableVertexAttribArray(feeds[savedAttrib].feedID);
    glBindVertexArray(0);

    if(!feeds[savedAttrib].isFed){
        feeds[savedAttrib].isFed = true;
        feedCounter--;
        if(feedCounter == 0) isFed = true;
    }
}

static GLint match_vAttrib(GLuint vAttrib, std::vector<GL4_Vertex>* feedsArg){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < feedsArg->size(); v++){
        if(feedsArg->at(v).feedID == vAttrib){
            savedAttrib = v;
            break;
        }
    }
    return savedAttrib;
}