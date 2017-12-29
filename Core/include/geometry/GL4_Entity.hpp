#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef GL4_ENTITY_H
    struct GL4_Entity_Feed {
        void feed(GLuint VAO, GLsizei size, const void *data);
        GLuint buffer;
        GLuint feedID;
        GLenum type = GL_FLOAT;
        GLenum usage = GL_STATIC_DRAW;
        GLboolean normalized = GL_FALSE;
        GLint perVertex;
        GLsizei stride;
        const GLvoid* offset;
        bool isFed = false;
    };

    class GL4_Entity {
    public:
        glm::mat4 relMatrix = glm::mat4(1);
        std::vector<GL4_Entity_Feed> entityFeeds;
        GLuint get_VAO(){ return VAO; }
        GLuint get_vertexCount(){ return vertexCount; }
        GLuint get_idxCount(){ return idxCount; }
        void drawXI(GLenum drawMode);
        void drawFixedXI(GLenum drawMode, GLuint drawCount);
        void drawPartXI(GLenum drawMode, GLuint part, GLuint whole);
        void draw(GLenum drawMode);
        void drawFixed(GLenum drawMode, GLuint drawCount);
        void drawPart(GLenum drawMode, GLuint part, GLuint whole);
        void dump(vertexFeed* vFeed);
        void dump(vertexFeedIdx* vFeed);
        void init();
        void feedPos(const void* data, GLuint vertexCount);
        void feedIdx(const void* startIdx, GLuint indexCount);
        void clearPos();
    protected:
        std::vector<GLfloat> mapPos();
        std::vector<GLuint> mapIdx();
        bool isFed = false;
        bool isIdx = false;
        GLuint perVertex = 3;
        GLuint VAO;
        GLuint posBff;
        GLuint vertexCount = 0;
        GLuint idxBff;
        GLuint idxCount = 0;
    };
#define GL4_ENTITY_H
#endif
