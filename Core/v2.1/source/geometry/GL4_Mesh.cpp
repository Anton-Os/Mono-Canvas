#include "geometry/GL4_Mesh.hpp"

static char error_elemNotFound[] = "Search for requested element failed";
static char error_nullPtrArgs[] = "Function invoked with null pointers as arguments";
static char error_drawNotFed[] = "Cannot perform draw, vertices haven't been fed";
static char error_drawNotIdx[] = "Cannot perform draw, indices not present";
static char error_initPhase[] = "Cannot proceed after initialization step";

static GLint match_vAttrib(GLuint vAttrib, std::vector<GL4_Vertex>* feedsArg){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < feedsArg->size(); v++){
        if(feedsArg->at(v).format->feedID == vAttrib){
            savedAttrib = v;
            break;
        }
    }
    return savedAttrib;
}

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

    std::vector<GLuint> buffers;
    buffers.resize(feeds.size());
    glGenBuffers(feeds.size(), buffers.data());

    for(unsigned v = 0; v < feeds.size(); v++) feeds[v].buffer = buffers[v];

    glGenVertexArrays(1, &VAO);
    initPhase = true;
}

void GL4_Mesh::add_feed(const GL4_Vertex_Format* format){
    if(initPhase) logError(__FILE__, __LINE__, error_initPhase);

    GL4_Vertex vertex;
    vertex.format = format;
    feeds.push_back(vertex);
    fin_counter++;
}

void GL4_Mesh::del_feed(GLuint vAttrib){
    GLint savedAttrib = match_vAttrib(vAttrib, &feeds);
    if(savedAttrib < 0) logError(__FILE__, __LINE__, error_elemNotFound);

    glBindVertexArray(VAO);
    glDisableVertexAttribArray(vAttrib);
    glBindVertexArray(0);

    feeds.erase(feeds.begin() + savedAttrib);
}

void GL4_Mesh::run_feed(GLuint vAttrib, const void * data, size_t size){
    if(!initPhase) init();

    GLint savedAttrib = match_vAttrib(vAttrib, &feeds);
    if(savedAttrib < 0) logError(__FILE__, __LINE__, error_elemNotFound);

    glBindBuffer(feeds[savedAttrib].format->target, feeds[savedAttrib].buffer);
    glBufferData(feeds[savedAttrib].format->target, size * feeds[savedAttrib].format->count * vertexCount, data, feeds[savedAttrib].format->usage);

    glBindVertexArray(VAO);
    if(feeds[savedAttrib].format->vaoPtrMode == _vaoPtrModes::Default)
        glVertexAttribPointer(feeds[savedAttrib].format->feedID, feeds[savedAttrib].format->count, feeds[savedAttrib].format->type, feeds[savedAttrib].format->normalized, 0, nullptr);
    else if(feeds[savedAttrib].format->vaoPtrMode == _vaoPtrModes::Integral)
        glVertexAttribIPointer(feeds[savedAttrib].format->feedID, feeds[savedAttrib].format->count, feeds[savedAttrib].format->type, 0, nullptr);
    else if(feeds[savedAttrib].format->vaoPtrMode == _vaoPtrModes::Integral)
        glVertexAttribIPointer(feeds[savedAttrib].format->feedID, feeds[savedAttrib].format->count, feeds[savedAttrib].format->type, 0, nullptr);

    glEnableVertexAttribArray(feeds[savedAttrib].format->feedID);
    glBindVertexArray(0);

    fin_counter--;
    if(fin_counter == 0) ready = true;
    else ready = false;
}
