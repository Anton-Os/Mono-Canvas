#ifndef PIPELINE_H
    #include "pipeline/Pipeline.hpp"
    #define PIPELINE_H
#endif

class GLSL_Waves : public GLSL_Base {
public:
    GLSL_Waves(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
        GLSL_Waves::shaderProgID = compileShaders(vertexShaderFilePath, fragmentShaderFilePath);
        glUseProgram(GLSL_Waves::shaderProgID);
        initUniforms();
    }
    enum unifID { mvpMatrix, renderMode, primMode, waveHeight, waveInc };
    void set_mvpMatrix(glm::mat4 mvpMatrix);
    void set_renderMode(GLuint renderMode);
    void set_primMode(GLuint primMode);
    void set_waveHeight(GLfloat waveHeight);
    void set_waveInc(GLfloat waveInc);
private:
    GLuint unifLoc[5];
    void initUniforms();
};