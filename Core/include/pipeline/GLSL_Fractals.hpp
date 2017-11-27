#ifndef PIPELINE_H
    #include "pipeline/Pipeline.hpp"
    #define PIPELINE_H
#endif

class GLSL_Fractals : public GLSL_Base {
public:
    GLSL_Fractals(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
        GLSL_Fractals::shaderProgID = compileShaders(vertexShaderFilePath, fragmentShaderFilePath);
        glUseProgram(GLSL_Fractals::shaderProgID);
        initUniforms();
    }
    enum unifID { mvpMatrix, iterCount };
    void set_mvpMatrix(glm::mat4 mvpMatrix);
    void set_iterCount(GLuint iterCount);
private:
    GLuint unifLoc[2];
    void initUniforms();
};