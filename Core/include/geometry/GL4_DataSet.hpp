#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef DATA_SET_H
    class GL4_DataSet {
    public:
        GL4_DataSet(GLvoid* data, GLint dataSize){
            init();
            create(data, dataSize);
        }
        GL4_DataSet(GLvoid* data, GLint dataSize, GLsizei stride, const GLvoid* offset){
            init();
            create(data, dataSize, stride, offset);
        }
        GL4_DataSet(GLint attribCount, GLvoid* data, GLint dataSize){
            init();
            create(attribCount, data, dataSize);
        }
        GL4_DataSet(GLint attribCount, GLvoid* data, GLint dataSize, GLsizei stride, const GLvoid* offset){
            init();
            create(attribCount, data, dataSize, stride, offset);
        }
        void init();
        void create(GLvoid* data, GLint dataSize);
        void create(GLint attribCount, GLvoid* data, GLint dataSize);
        void create(GLvoid* data, GLint dataSize, GLsizei stride, const GLvoid* offset);
        void create(GLint attribCount, GLvoid* data, GLint dataSize, GLsizei stride, const GLvoid* offset);
        void index(GLvoid* data, GLint dataSize);
        void draw(GLenum drawMode, GLuint drawCount);
        void drawIdx(GLenum drawMode, GLuint indexCount);
    private:
        enum feedParams {VAO, feedPos};
        GLuint feed[2];
    };

#define DATA_SET_H
#endif