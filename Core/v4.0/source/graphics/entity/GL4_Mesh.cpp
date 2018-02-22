#include "graphics/entity/GL4_Mesh.hpp"

static char error_elemNotFound[] = "Search for requested element failed";
static char error_nullPtrArgs[] = "Function invoked with null pointers as arguments";
static char error_drawNotFed[] = "Cannot perform draw, vertices haven't been fed";
static char error_drawNotIdx[] = "Cannot perform draw, indices not present";
static char error_initPhase[] = "Cannot proceed after initialization step";
static char error_initAddFeed[] = "Cannot add a feed after call to set_feed";
static char error_noData[] = "Mesh has no data and cannot be initialized";
static char error_vertexIssue[] = "Vertex count is inconsistent";

static GLint match_vAttrib(GLuint vAttrib, std::vector<GL4_Vertex>* feeds_arg){
    GLint savedAttrib = -1;
    for(unsigned v = 0; v < feeds_arg->size(); v++){
        if(feeds_arg->at(v).format->mFeedID == vAttrib){
            savedAttrib = v;
            break;
        }
    }
    return savedAttrib;
}

void GL4_Mesh::Order::init(const GLuint* VAO_arg){
    if(mInitPhase) logError(__FILE__, __LINE__, error_initPhase);

    mVAO_ptr = VAO_arg;
}

void GL4_Mesh::Order::feed(GLuint* data_arg, GLuint count_arg){
    indexCount = count_arg;
    //size = size_arg;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indexCount, (void*)data_arg, GL_STATIC_DRAW);
    isIdx = true;
}

void GL4_Mesh::Order::feed(GLuint VAO_arg, GLuint* data_arg, GLuint count_arg){
    indexCount = count_arg;
    //size = size_arg;
    glBindVertexArray(VAO_arg);
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indexCount, (void*)data_arg, GL_STATIC_DRAW);
    glBindVertexArray(0);
    isIdx = true;
}

void GL4_Mesh::Quill::init(const GLuint* VAO_arg, const GLboolean* isFed_arg, const GLboolean* isIdx_arg, const GLuint* vertexCount_arg, const GLuint* indexCount_arg){
    if(mInitPhase) logError(__FILE__, __LINE__, error_initPhase);
    
    if(nullptr == VAO_arg || nullptr == isFed_arg || nullptr == isIdx_arg || nullptr == vertexCount_arg || nullptr == indexCount_arg)
        logError(__FILE__, __LINE__, error_nullPtrArgs);

    vao_ptr = VAO_arg;
    isFed_ptr = isFed_arg;
    isIdx_ptr = isIdx_arg;
    vertexCount_ptr = vertexCount_arg;
    indexCount_ptr = indexCount_arg;
    mInitPhase = true;
}

void GL4_Mesh::Quill::unordered_draw(){
    if(! *isFed_ptr) logError(__FILE__, __LINE__, error_drawNotFed);

    glBindVertexArray(*vao_ptr);
    glDrawArrays(mode, 0, *vertexCount_ptr);
    glBindVertexArray(0);
}

void GL4_Mesh::Quill::ordered_draw(){
    if(! *isFed_ptr) logError(__FILE__, __LINE__, error_drawNotFed);
    if(! *isIdx_ptr) logError(__FILE__, __LINE__, error_drawNotIdx);
    
    glBindVertexArray(*vao_ptr);
    glDrawElements(mode, *indexCount_ptr, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_Mesh::init(){
    if(mFeeds.empty()) logError(__FILE__, __LINE__, error_drawNotFed);

    std::vector<GLuint> buffers;
    buffers.resize(mFeeds.size());
    glGenBuffers(mFeeds.size(), buffers.data());

    for(unsigned v = 0; v < mFeeds.size(); v++) mFeeds[v].buffer = buffers[v];

    glGenVertexArrays(1, &mVAO);
    mInitPhase = true;
}

void GL4_Mesh::add_feed(const GL4_Vertex_Format* format){
    if(mInitPhase) logError(__FILE__, __LINE__, error_initAddFeed);

    GL4_Vertex vertex;
    vertex.format = format;
    mFeeds.push_back(vertex);
    mFin_counter++;
}

void GL4_Mesh::del_feed(_GL4_Vertex_Feed_ID::Pick pick_arg){
    GLint savedAttrib = match_vAttrib(pick_arg, &mFeeds);
    if(savedAttrib < 0) logError(__FILE__, __LINE__, error_elemNotFound);

    glBindVertexArray(mVAO);
    glDisableVertexAttribArray(pick_arg);
    glBindVertexArray(0);

    mFeeds.erase(mFeeds.begin() + savedAttrib);
}

void GL4_Mesh::set_feed_data(_GL4_Vertex_Feed_ID::Pick pick_arg, const void * data, size_t size){
    if(!mInitPhase) init();

    GLint savedAttrib = match_vAttrib(pick_arg, &mFeeds);
    if(savedAttrib < 0) logError(__FILE__, __LINE__, error_elemNotFound);

    glBindBuffer(mFeeds[savedAttrib].format->mTarget, mFeeds[savedAttrib].buffer);
    glBufferData(mFeeds[savedAttrib].format->mTarget, size * mFeeds[savedAttrib].format->mCount * mVertexCount, data, mFeeds[savedAttrib].format->mUsage);

    glBindVertexArray(mVAO);
    if(mFeeds[savedAttrib].format->mVaoPtrMode == _vaoPtrModes::Default)
        glVertexAttribPointer(mFeeds[savedAttrib].format->mFeedID, mFeeds[savedAttrib].format->mCount, mFeeds[savedAttrib].format->mType, mFeeds[savedAttrib].format->mNormalized, 0, nullptr);
    else if(mFeeds[savedAttrib].format->mVaoPtrMode == _vaoPtrModes::Integral)
        glVertexAttribIPointer(mFeeds[savedAttrib].format->mFeedID, mFeeds[savedAttrib].format->mCount, mFeeds[savedAttrib].format->mType, 0, nullptr);
    else if(mFeeds[savedAttrib].format->mVaoPtrMode == _vaoPtrModes::Double)
        glVertexAttribLPointer(mFeeds[savedAttrib].format->mFeedID, mFeeds[savedAttrib].format->mCount, mFeeds[savedAttrib].format->mType, 0, nullptr);

    glEnableVertexAttribArray(mFeeds[savedAttrib].format->mFeedID);
    glBindVertexArray(0);

    mFin_counter--;
    if(mFin_counter == 0) mReady = true;
    else mReady = false;
}