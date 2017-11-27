#ifndef PIPELINE_H
    #include "pipeline/Pipeline.hpp"
    #define PIPELINE_H
#endif

class GLSL_Idle : public GLSL_Base {
public:
    GLSL_Idle(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
        GLSL_Idle::shaderProgID = compileShaders(vertexShaderFilePath, fragmentShaderFilePath);
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

