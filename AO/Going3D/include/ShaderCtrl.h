
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

namespace LitEnv_UniformIndex {
    enum LitEnv_UniformIndex {
        worldMatrix,
        localMatrix,
        testBlock,
        materialBlock,
        lightSourceBlock
    };
};

struct TestBlock {
    GLfloat Red;
    GLfloat Green;
    GLfloat Blue;
};

struct litEnv_UniformData {
    glm::mat4 worldMatrix;
    glm::mat4 localMatrix;

    MaterialBlock materialBlock;
    LightSourceBlock lightSourceBlock;
};

class LitEnv : public AnyShader {
public:
    LitEnv(GLuint shaderProg){
        shaderProgID = shaderProg;
    }

    void worldMatrix(litEnv_UniformData* Uniforms);
    void localMatrix(litEnv_UniformData* Uniforms);
    void testBlock(litEnv_UniformData* Uniforms, TestBlock* testBlock);
    void materialBlock(litEnv_UniformData* Uniforms, MaterialBlock* materialBlock);
    void materialBlock(litEnv_UniformData* Uniforms, MaterialBlock materialBlock);
    void lightSourceBlock(litEnv_UniformData* Uniforms, LightSourceBlock* lightSourceBlock);

    void setUniforms(litEnv_UniformData* Uniforms);
    void setUniforms(litEnv_UniformData* Uniforms, ModelComposite* Model);
private:
    GLuint UBO[2];
};