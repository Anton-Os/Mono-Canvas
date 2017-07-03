#include "Common.h"

class Model3D {
    public:
        GLuint createMode;
        
        void createModel(GLfloat* vertexData, GLsizei dataSize){
            createMode = 1;
        }

        void createModel(GLfloat* vertexData, GLsizei dataSize, GLuint* vertexIndices, GLsizei indicesSize){
            createMode = 2;
        }

        void createModel(GLfloat* vertexData, GLsizei dataSize, GLuint* vertexIndices, GLsizei indicesSize, 
                         GLfloat* texCoord, GLsizei texCoordSize, GLfloat* normals, GLsizei normalsSize){
            createMode = 3;
        }

        void destroyModel(){

        }
};