
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

namespace LitEnv_UNI {
    enum LitEnv_UNI {
        mvMatrix,
        mvpMatrix,
        nMatrix,
        lightSourcePos
    };
};

struct litEnv_UniformData {
    glm::mat4 worldMatrix;
    glm::mat4 localMatrix;
    // std::array<GLfloat, 3> cameraPos;
    glm::vec3 cameraPos;

    MaterialBlock materialBlock;
    LightSourceBlock lightSourceBlock;
};

class LitEnv : public AnyShader {
public:
    LitEnv(GLuint shaderProg){
        shaderProgID = shaderProg;
    }
    void mvMatrix(glm::mat4 mvMatrix);
    void mvpMatrix(glm::mat4 mvpMatrix);
    void nMatrix(glm::mat3 nMatrix);
    void lightSourcePos(std::array<GLfloat, 3> lightSourcePos);
    void materialBlock(MaterialBlock* materialBlock);
    // void lightSourceBlock(LightSourceBlock* lightSourceBlock);

    void setUniforms();
    void setUniforms(litEnv_UniformData* Uniforms);
    void setUniforms(litEnv_UniformData* Uniforms, ModelComposite* Model);
private:
    GLuint SSBO[2];
};