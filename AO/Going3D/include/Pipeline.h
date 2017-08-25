
class BaseShader {
protected:
    BaseShader(GLuint shaderProg){ 
        shaderProgID = shaderProg;
    }
    GLuint shaderProgID;
};

namespace CF_UNIF {
    enum CF_UNIF {
        mvMatrix,
        mvpMatrix,
        nMatrix,
        camPos
    };
};

class CamFlash : public BaseShader {
public:
    CamFlash(GLuint shaderProg) : BaseShader(shaderProg){ }
    void mvMatrix(glm::mat4 mvMatrix);
    void mvpMatrix(glm::mat4 mvpMatrix);
    void nMatrix(glm::mat3 nMatrix);
    void camPos(glm::vec3 camPos);
    void materialBlock(MaterialBlock* materialBlock);
    void setUniforms();
private:
    GLint unifLoc[4];
    GLuint SSBO;
};