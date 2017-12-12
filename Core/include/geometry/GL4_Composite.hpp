#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

// WORK IN PROGRESS!!!!!!!!!!!

#ifndef COMPOSITE_H
    class GL4_Composite {
    public:
        glm::mat4 relMatrix = glm::mat4(1);
        GLuint get_vertexCount(GLuint targetBff){ return vertexCount; }
        GLuint get_idxCount(GLuint targetBff){ return idxCount; }
        void drawXI(GLenum drawMode);
        void draw(GLenum drawMode);
    protected:
        std::vector<GLfloat> mapPos(GLuint targetBff);
        std::vector<GLuint> mapIdx(GLuint targetBff);
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
