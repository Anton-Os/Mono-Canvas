
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

namespace SPH_UNIF {
    enum SPH_UNIF {
        mvpMatrix,
        nMatrix,
        renderMode,
        sphereParams,
        gradient
    };
};

struct ColorPalette4x3 {
    std::array<GLfloat, 3> color1;
    std::array<GLfloat, 3> color2;
    std::array<GLfloat, 3> color3;
    std::array<GLfloat, 3> color4;
};

struct SphereParams {
    GLfloat sliceCount;
    GLfloat stackCount;
};

class Sphere : public BaseShader {
public:
    Sphere(GLuint shaderProg) : BaseShader(shaderProg){ }
    void mvpMatrix(glm::mat4 mvpMatrix);
    void nMatrix(glm::mat3 nMatrix);
    void renderMode(GLuint renderMode);
    void colorPalette(ColorPalette4x3* colorPalette);
    void sphereParams(std::array<GLuint, 2> sphereParams);
    void gradient(std::array<GLfloat, 6> gradient);
    void initUniforms();
private:
    GLint unifLoc[5];
    GLuint SSBO[2];
};