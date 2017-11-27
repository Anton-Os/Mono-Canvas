#ifndef PIPELINE_H
    #include "pipeline/Pipeline.hpp"
    #define PIPELINE_H
#endif

class GLSL_HeightRange : public GLSL_Base {
public:
    GLSL_HeightRange(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
        GLSL_HeightRange::shaderProgID = compileShaders(vertexShaderFilePath, fragmentShaderFilePath);
        glUseProgram(GLSL_HeightRange::shaderProgID);
        initUniforms();
    }
    // GLSL_HeightRange(GLuint shaderProg) : GLSL_Base(shaderProg){}
    enum unifID { mvpMatrix, heightRange, rise, renderMode };
    void set_mvpMatrix(glm::mat4 mvpMatrix);
    void set_heightRange(GLfloat min, GLfloat max);
    void set_rise(GLfloat rise);
    void set_renderMode(GLuint renderMode);
    void initUniforms();
private:
    GLuint unifLoc[4];
};