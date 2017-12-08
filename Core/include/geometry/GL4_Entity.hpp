#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef ENTITY_H
    class GL4_Entity {
    public:
        glm::mat4 relMatrix = glm::mat4(1);
        GLuint get_vertexCount(){ return vertexCount; }
        GLuint get_idxCount(){ return idxCount; }
        void drawXI(GLenum drawMode);
        void drawFixedXI(GLenum drawMode, GLuint drawCount);
        void drawPartXI(GLenum drawMode, GLuint part, GLuint whole);
        void draw(GLenum drawMode);
        void drawFixed(GLenum drawMode, GLuint drawCount);
        void drawPart(GLenum drawMode, GLuint part, GLuint whole);
        void feed(vertexFeed* vFeed);
        void feed(vertexFeedIdx* vFeed);
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
#define ENTITY_H
#endif
