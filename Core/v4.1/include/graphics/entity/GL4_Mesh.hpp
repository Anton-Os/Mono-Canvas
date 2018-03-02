#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "graphics/GL4_Vertex.hpp"
#endif

#ifndef GL4_MESH_H
    class GL4_Mesh {
    public:
        GL4_Mesh(const GLuint* VAO_arg, const GLuint* indexBuffer_arg, GLuint vertexCount_arg, std::vector<GL4_Vertex_Feed>* feeds_arg){
            mVAO = VAO_arg;
            mVertexCount = vertexCount_arg;
            mFeeds.swap(*feeds_arg);
            mFeedBits.assign(mFeeds.size(), false);
            mFeedCount = mFeeds.size();
        }
        // void add_feed(const GLuint* buffer_arg, const GL4_Vertex_Format* vertexFormat_arg, const void* data);
        // void del_feed(_GL4_Vertex_Feed_ID::Pick vertexFeed_arg);
        void set_feed_data(_GL4_Vertex_Feed_ID::Pick vertexFeed_arg, const void* data);
        void set_index_data(GLuint indexCount_arg, const void* data_arg);
        void unordered_draw();
        // void unordered_drawFixed(GLuint count);
        // void unordered_drawPart(GLuint part, GLuint whole);
        void ordered_draw();
        // void ordered_drawFixed(GLuint count);
        // void ordered_drawPart(GLuint part, GLuint whole);
    private:
	GLfloat* mTransform = nullptr;
        const GLuint* mVAO = nullptr;
        const GLuint* mIndexBuffer = nullptr;
        GLboolean mFed = false;
        GLboolean mIdx = false;
        GLuint mFeedCount;
        std::vector<bool> mFeedBits;
        std::vector<GL4_Vertex_Feed> mFeeds;
        GLuint mIndexCount;
        GLuint mVertexCount;
        GLenum mIndexType = GL_UNSIGNED_INT;
        GLenum mDrawMode = GL_TRIANGLES;
        GLenum mBufferUsage = GL_STATIC_DRAW;
    };
#define GL4_MESH_H
#endif
