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
            mQuill.init(&mReady, mOrder.get_isIdx(), &mVAO, &mVertexCount, mOrder.get_indexCount());
        }
        class Order {
        public:
            GLboolean* get_isIdx(){ return &isIdx; }
            GLuint* get_indexCount(){ return &indexCount; }
            void feed(GLuint* data_arg, GLuint count_arg);
            void feed(GLuint VAO_arg, GLuint* data_arg, GLuint count_arg);
        private:
            GLboolean isIdx = false;
            GLuint indexCount;
            GLuint buffer;
            GLenum target = GL_ELEMENT_ARRAY_BUFFER;
            size_t size;
            // GLenum type = GL_UNSIGNED_INT;
        } mOrder;
        class Quill {
        public:
            GLenum mode = GL_TRIANGLES;
            void init(const GLboolean* fed, const GLboolean* idx, const GLuint* o, const GLuint* v, const GLuint* i);
            void unordered_draw();
            void unordered_drawFixed(GLuint count);
            void unordered_drawPart(GLuint part, GLuint whole);
            void ordered_draw();
            void ordered_drawFixed(GLuint count);
            void ordered_drawPart(GLuint part, GLuint whole);
        private:
            GLboolean mInit_phase = false;
            const GLboolean* isFedPtr = nullptr;
            const GLboolean* isIdxPtr = nullptr;
            const GLuint* vaoPtr = nullptr;
            const GLuint* vertexCountPtr = nullptr;
            const GLuint* indexCountPtr = nullptr;
        } mQuill;
        void init();
        void add_feed(const GL4_Vertex_Format* vertexFeed);
        void del_feed(_GL4_Vertex_Feed_ID::Pick pick_arg);
        void set_feed(_GL4_Vertex_Feed_ID::Pick pick_arg, const void* data, size_t size);
        GLuint get_VAO(){ return mVAO; }
    private:
        GLushort mFin_counter = 0;
        GLboolean mReady = false;
        std::vector<GL4_Vertex> mFeeds;
        GLuint mVAO;
        GLboolean mInit_phase = false;
        GLuint mVertexCount;
    };
#define GL4_MESH_H
#endif