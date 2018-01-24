#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "geometry/GL4_Vertex.hpp"
#endif

#ifndef GL4_MESH_H
    // Helper functions

    static GLint match_vAttrib(GLuint vAttrib, std::vector<GL4_Vertex>* feedsArg);

    // Subset of GL4_Mesh responsible for indexing

    struct GL4_Mesh_Order {
        GLboolean isIdx = false;
        GLuint indexCount;
        GLuint buffer;
        GLenum target = GL_ELEMENT_ARRAY_BUFFER;
        GLenum type = GL_UNSIGNED_INT;
        void feed(const void* data, size_t size, GLuint count);
    };

    // Subset of GL4_Mesh responsible for rendering

    class GL4_Mesh_Quill {
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
        GLboolean initPhase = false;
        const GLboolean* isFedPtr = nullptr;
        const GLboolean* isIdxPtr = nullptr;
        const GLuint* vaoPtr = nullptr;
        const GLuint* vertexCountPtr = nullptr;
        const GLuint* indexCountPtr = nullptr;
    };

    class GL4_Mesh {
    public:
        GL4_Mesh(GLuint v){
            vertexCount = v;
            quill.init(&ready, &order.isIdx, &VAO, &vertexCount, &order.indexCount);
        }
        GL4_Mesh_Order order;
        GL4_Mesh_Quill quill;
        void init();
        // void add_feed(GL4_Vertex* vertexFeed);
        void add_feed(const GL4_Vertex_Format* vertexFeed);
        void del_feed(GLuint vAttrib);
        void run_feed(GLuint vAttrib, const void* data, size_t size);
    private:
        GLushort fin_counter = 0;
        GLboolean ready = false;
        std::vector<GL4_Vertex> feeds;
        GLuint VAO;
        GLboolean initPhase = false;
        GLuint vertexCount;
    };
#define GL4_MESH_H
#endif