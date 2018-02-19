#define PIPELINE_X
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
        GL4_Mesh(GLuint v){
            mVertexCount = v;
            mQuill.init(mVAO_ptr, mReady_ptr, mOrder.mIsIdx_ptr, mVertexCount_ptr, mOrder.mIndexCount_ptr);
            mOrder.init(mVAO_ptr);
        }
        class Order {
        public:
            void init(const GLuint* VAO_arg);
            void feed(GLuint* data_arg, GLuint count_arg);
            void feed(GLuint VAO_arg, GLuint* data_arg, GLuint count_arg);
            const GLboolean *const mIsIdx_ptr = &isIdx;
            const GLuint *const mIndexCount_ptr = &indexCount;
        private:
            const GLuint* mVAO_ptr = nullptr;
            GLboolean mInitPhase = false;
            GLboolean isIdx = false;
            GLuint indexCount;
            GLuint buffer;
            GLenum target = GL_ELEMENT_ARRAY_BUFFER;
        } mOrder;
        class Quill {
        public:
            GLenum mode = GL_TRIANGLES;
            void init(const GLuint* o, const GLboolean* fed, const GLboolean* idx, const GLuint* v, const GLuint* i);
            void unordered_draw();
            void unordered_drawFixed(GLuint count);
            void unordered_drawPart(GLuint part, GLuint whole);
            void ordered_draw();
            void ordered_drawFixed(GLuint count);
            void ordered_drawPart(GLuint part, GLuint whole);
        private:
            GLboolean mInitPhase = false;
            const GLboolean* isFed_ptr = nullptr;
            const GLboolean* isIdx_ptr = nullptr;
            const GLuint* vao_ptr = nullptr;
            const GLuint* vertexCount_ptr = nullptr;
            const GLuint* indexCount_ptr = nullptr;
        } mQuill;
        void init();
        void add_feed(const GL4_Vertex_Format* vertexFeed);
        void del_feed(_GL4_Vertex_Feed_ID::Pick pick_arg);
        void set_feed(_GL4_Vertex_Feed_ID::Pick pick_arg, const void* data, size_t size);
        const GLboolean *const mReady_ptr = &mReady;
        const GLuint *const mVAO_ptr = &mVAO;
        const GLuint *const mVertexCount_ptr = &mVertexCount;
    private:
        GLushort mFin_counter = 0;
        GLboolean mReady = false;
        std::vector<GL4_Vertex> mFeeds;
        GLuint mVAO;
        GLboolean mInitPhase = false;
        GLuint mVertexCount;
    };
#define GL4_MESH_H
#endif