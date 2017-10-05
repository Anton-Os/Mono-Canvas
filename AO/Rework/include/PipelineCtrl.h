#include <iostream>
#include <array>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BaseShader {
protected:
    BaseShader(GLuint shaderProg){ 
        shaderProgID = shaderProg;
    }
    GLuint shaderProgID;
};

namespace LK_UNIF {
    enum LK_UNIF {
        mvpMatrix,
        msTimer
    };
};

class Locked : public BaseShader {
public:
    Locked(GLuint shaderProg) : BaseShader(shaderProg){}
    void mvpMatrix(glm::mat4 mvpMatrix);
    void msTimer(std::array<GLuint, 2> msTimer);
    void initUniforms();
private:
    GLuint unifLoc[2];
};