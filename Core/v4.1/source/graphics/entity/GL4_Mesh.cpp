#include "graphics/entity/GL4_Mesh.hpp"

static char error_vaoNull[] = "Vertex Array not properly initialized";
static char error_vboNull[] = "Buffer not properly initialized";
static char error_feedNotFound[] = "Vertex feed couldnt be found";
static char error_notFed[] = "Mesh is not fed to OpenGL";

GL4_Mesh::GL4_Mesh(GLuint vertexCount_arg, std::initializer_list<GL4_Vertex_Format*> formats_arg){
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
    std::vector<GLuint> buffers;
    buffers.resize(formats_arg.size() + 1);
    glGenBuffers(formats_arg.size() + 1, buffers.data());
    mIndexBuffer = buffers[0];
    for(unsigned buffer_elem = 1; buffer_elem < buffers.size(); buffer_elem++)
        mFeeds.push_back(GL4_Vertex_Feed(buffers[buffer_elem], *(formats_arg.begin() + buffer_elem - 1)));
    glBindVertexArray(0);
    mVertexCount = vertexCount_arg;
    mFeedCount = mFeeds.size();
    mFeedBits.resize(mFeeds.size());
}

void GL4_Mesh::set_feed_data(_GL4_Vertex_Feed_ID::Pick vertexFeed_arg, const void* data_arg){
    GLuint currentIndex = mFeeds.size();
    for(unsigned index_elem = 0; index_elem < mFeeds.size(); index_elem++){
        if(mFeeds[index_elem].mFormat->get_feedID() != vertexFeed_arg) continue;
        else {
            currentIndex = index_elem;
            break;
        }
    }
    if(currentIndex == mFeeds.size()) logError(__FILE__, __LINE__, error_feedNotFound);
    
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mFeeds[currentIndex].get_buffer());
    glBufferData(GL_ARRAY_BUFFER, mFeeds[currentIndex].mFormat->get_size() * mFeeds[currentIndex].mFormat->get_count() * mVertexCount, data_arg, mBufferUsage);

    if(!mFeedBits[currentIndex]){
        if(mFeeds[currentIndex].mFormat->get_vaoPtrMode() == _vaoPtrModes::Default)
            glVertexAttribPointer(mFeeds[currentIndex].mFormat->get_feedID(), mFeeds[currentIndex].mFormat->get_count(), mFeeds[currentIndex].mFormat->get_type(), mFeeds[currentIndex].mFormat->get_normalized(), 0, nullptr);
        else if(mFeeds[currentIndex].mFormat->get_vaoPtrMode() == _vaoPtrModes::Integral)
            glVertexAttribIPointer(mFeeds[currentIndex].mFormat->get_feedID(), mFeeds[currentIndex].mFormat->get_count(), mFeeds[currentIndex].mFormat->get_type(), 0, nullptr);
        else if(mFeeds[currentIndex].mFormat->get_vaoPtrMode() == _vaoPtrModes::Double)
            glVertexAttribLPointer(mFeeds[currentIndex].mFormat->get_feedID(), mFeeds[currentIndex].mFormat->get_count(), mFeeds[currentIndex].mFormat->get_type(), 0, nullptr);
        glEnableVertexAttribArray(mFeeds[currentIndex].mFormat->get_feedID());

        mFeedBits[currentIndex] = true;
        mFeedCount--;
        if(mFeedCount == 0) mFed = true;
    }
    
    glBindBuffer(0, GL_ARRAY_BUFFER);
    glBindVertexArray(0);
}

void GL4_Mesh::unordered_draw(){
    if(!mFed) logError(__FILE__, __LINE__, error_notFed);
    glBindVertexArray(mVAO);
    glDrawArrays(mDrawMode, 0, mVertexCount);
    glBindVertexArray(0);
}
