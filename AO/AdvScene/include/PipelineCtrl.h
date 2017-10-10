#include <iostream>
#include <array>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLSL_Base {
protected:
    GLSL_Base(GLuint shaderProg){ 
        shaderProgID = shaderProg;
    }
    GLuint shaderProgID;
};

class GLSL_Idle : public GLSL_Base {
public:
    GLSL_Idle(GLuint shaderProg) : GLSL_Base(shaderProg){}
    enum unifID { mvpMatrix };
    void set_mvpMatrix(glm::mat4 mvpMatrix);
    void initUniforms();
private:
    GLuint unifLoc[1];
};

class GLSL_HeightRange : public GLSL_Base {
public:
    GLSL_HeightRange(GLuint shaderProg) : GLSL_Base(shaderProg){}
    enum unifID { mvpMatrix, heightRange, rise };
    void set_mvpMatrix(glm::mat4 mvpMatrix);
    void set_heightRange(GLfloat min, GLfloat max);
    void set_rise(GLfloat rise);
    void initUniforms();
private:
    GLuint unifLoc[3];
};
