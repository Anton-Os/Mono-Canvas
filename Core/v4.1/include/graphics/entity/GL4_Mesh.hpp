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
        GL4_Mesh(const GLuint* VAO_arg, GLuint vertexCount_arg){
            mVAO = VAO_arg;
            mVertexCount = vertexCount_arg;
        }
        void add_feed(const GLuint* buffer_arg, const GL4_Vertex_Format* vertexFormat_arg);
        void del_feed(_GL4_Vertex_Feed_ID::Pick vertexFeed_arg);
        void set_feed_data(_GL4_Vertex_Feed_ID::Pick vertexFeed_arg, const void* data);
        void set_feed_data(const GLuint* buffer_arg, const GL4_Vertex_Format* vertexFormat_arg, const void* data);
        void set_index_data(const void* data_arg);
        void set_index_data(const GLuint* indexBuffer_arg, const void* data_arg);
        void unordered_draw();
        // void unordered_drawFixed(GLuint count);
        // void unordered_drawPart(GLuint part, GLuint whole);
        void ordered_draw();
        // void ordered_drawFixed(GLuint count);
        // void ordered_drawPart(GLuint part, GLuint whole);
    private:
        const GLuint* mVAO = nullptr;
        const GLuint* mIndexBuffer = nullptr;
        GLushort mFeedCountdown = 0;
        GLboolean mFed = false;
        GLboolean mIdx = false;
        std::vector<GL4_Vertex_Feed> mFeeds;
        GLuint mIndexCount;
        GLuint mVertexCount;
        GLenum mIndexType = GL_UNSIGNED_INT;
        GLenum mDrawMode = GL_TRIANGLES;
    };
#define GL4_MESH_H
#endif