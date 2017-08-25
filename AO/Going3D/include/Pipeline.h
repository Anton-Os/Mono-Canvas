
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
        nMatrix
    };
};

class CamFlash : public BaseShader {
public:
    CamFlash(GLuint shaderProg) : BaseShader(shaderProg){ }
    void mvMatrix(glm::mat4 mvMatrix);
    void mvpMatrix(glm::mat4 mvpMatrix);
    void nMatrix(glm::mat3 nMatrix);
    void materialBlock(MaterialBlock* materialBlock);
    void initUniforms();
private:
    GLint unifLoc[3];
    GLuint SSBO[1];
};