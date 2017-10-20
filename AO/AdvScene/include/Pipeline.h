#include <iostream>
#include <array>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Loaders.h"

class GLSL_Base {
protected:
    GLSL_Base(GLuint shaderProg){ 
        shaderProgID = shaderProg;
    }
    GLuint shaderProgID;
};

class GLSL_Idle : public GLSL_Base {
public:
    GLSL_Idle(GLuint shaderProg) : GLSL_Base(shaderProg) {
        glUseProgram(GLSL_Idle::shaderProgID);
        initUniforms();
    }
    enum unifID { mvpMatrix, renderMode };
    void set_mvpMatrix(glm::mat4 mvpMatrix);
    void set_renderMode(GLuint renderMode);
private:
    GLuint unifLoc[2];
    void initUniforms();
};

class GLSL_HeightRange : public GLSL_Base {
public:
    GLSL_HeightRange(GLuint shaderProg) : GLSL_Base(shaderProg){}
    enum unifID { mvpMatrix, heightRange, rise, renderMode };
    void set_mvpMatrix(glm::mat4 mvpMatrix);
    void set_heightRange(GLfloat min, GLfloat max);
    void set_rise(GLfloat rise);
    void set_renderMode(GLuint renderMode);
    void initUniforms();
private:
    GLuint unifLoc[4];
};