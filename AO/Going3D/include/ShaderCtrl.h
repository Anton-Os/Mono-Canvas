
class AnyShader {
protected:
    GLuint shaderProgID;
    std::vector<GLint> uniformLocation;
};

namespace NoBlocks_UniformIndex {
    enum NoBlocks_UniformIndex {
        worldMatrix,
        localMatrix,
        defaultColor,
        surfaceRenderMode
    };
};

struct noBlocks_UniformData {
    glm::mat4 worldMatrix;
    glm::mat4 localMatrix;

    std::array<GLfloat, 4> defaultColor;
    GLuint surfaceRenderMode;
};

class NoBlocks : public AnyShader {
public:
    NoBlocks(GLuint shaderProg){
        shaderProgID = shaderProg;
    }
    void worldMatrix(noBlocks_UniformData* noBlocks_Uniforms);
    void localMatrix(noBlocks_UniformData* noBlocks_Uniforms);
    void defaultColor(noBlocks_UniformData* noBlocks_Uniforms);
    void surfaceRenderMode(noBlocks_UniformData* noBlocks_Uniforms);
    
    void setUniforms(noBlocks_UniformData* noBlocks_Uniforms);
};

class BaseShader {
protected:
    BaseShader(GLuint shaderProg){ 
        shaderProgID = shaderProg;
    }
    GLuint shaderProgID;
};

namespace LE_UNIF {
    enum LE_UNIF {
        mvMatrix,
        mvpMatrix,
        nMatrix
    };
};

class LitEnv : public BaseShader {
public:
    LitEnv(GLuint shaderProg) : BaseShader(shaderProg){ }
    void mvMatrix(glm::mat4 mvMatrix);
    void mvpMatrix(glm::mat4 mvpMatrix);
    void nMatrix(glm::mat3 nMatrix);
    void materialBlock(MaterialBlock* materialBlock);
    void initUniforms();
private:
    GLint unifLoc[3];
    GLuint SSBO[1];
};