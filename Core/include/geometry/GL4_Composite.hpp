#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

// WORK IN PROGRESS!!!!!!!!!!!

#ifndef COMPOSITE_H
    class GL4_Composite {
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
    protected:
        std::vector<GLfloat> mapPos();
        std::vector<GLuint> mapIdx();
        bool isFed = false;
        bool isIdx = false;
        GLuint perVertex = 3;
        std::vector<GLuint> VAOs;
        std::vector<GLuint> posBffs;
        std::vector<GLuint> vertexCounts;
        std::vector<GLuint> idxBffs;
        std::vector<GLuint> idxCounts;
    };
#define COMPOSITE_H
#endif
