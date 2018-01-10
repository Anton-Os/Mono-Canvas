#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef GL4_MESH_H
    namespace vaoPtrModes {
        enum Modes {
            Default, 
            Integral, 
            Double 
        };
    }

    // Subset of GL4_Mesh providing a vertex attribute

    struct GL4_Mesh_VertexFeed {
        GLboolean isFed;
        GLuint buffer;
        GLint count = 3;
        GLint feedID = 0;
        GLenum target = GL_ARRAY_BUFFER;
        GLenum type = GL_FLOAT;
        GLenum usage = GL_STATIC_DRAW;
        GLboolean normalized = GL_FALSE;
        int vaoPtrMode = vaoPtrModes::Default;
    };

    // Subset of GL4_Mesh responsible for indexing

    struct GL4_Mesh_Order {
        GLboolean isIdx;
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
        void init(GLboolean* fed, GLboolean* idx, GLuint* v, GLuint* i);
        void unordered_draw();
        void unordered_drawFixed(GLuint count);
        void unordered_drawPart(GLuint part, GLuint whole);
        void ordered_draw();
        void ordered_drawFixed(GLuint count);
        void ordered_drawPart(GLuint part, GLuint whole);
    private:
        GLboolean initPhase;
        GLboolean* isFedPtr = nullptr;
        GLboolean* isIdxPtr = nullptr;
        GLuint* vertexCountPtr = nullptr;
        GLuint* indexCountPtr = nullptr;
    };

    class GL4_Mesh {
    public:
        GL4_Mesh(GLushort c, GLuint v){
            vertexCount = v;
            feedCounter = c;
            quill.init(&isFed, &order.isIdx, &vertexCount, &order.indexCount);
            init();
        }
        std::vector<GL4_Mesh_VertexFeed> vertices;
        GL4_Mesh_Order order;
        GL4_Mesh_Quill quill;
        void feed(GLuint vAttrib, const void* data, size_t size);
        void init();
    private:
        GLuint VAO;
        GLushort feedCounter;
        GLboolean isFed = false;
        GLuint vertexCount;
    };
#define GL4_MESH_H
#endif