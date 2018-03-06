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
    struct GL4_Mesh_Transform {
        GLfloat* mData;
        GLuint mCount;
    };

    class GL4_Mesh {
    public:
        GL4_Mesh(GLuint vertexCount_arg, std::initializer_list<GL4_Vertex_Format*> formats_arg);
        void set_feed_data(_GL4_Vertex_Feed_ID::Pick vertexFeed_arg, const void* data);
        void set_index_data(GLuint indexCount_arg, const void* data_arg);
        void unordered_draw();
        // void unordered_drawFixed(GLuint count);
        // void unordered_drawPart(GLuint part, GLuint whole);
        void ordered_draw();
        // void ordered_drawFixed(GLuint count);
        // void ordered_drawPart(GLuint part, GLuint whole);
    private:
	    GL4_Mesh_Transform transform;
        GLuint mVAO;
        GLuint mIndexBuffer;
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
