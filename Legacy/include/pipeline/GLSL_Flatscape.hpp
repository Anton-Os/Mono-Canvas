#ifndef PIPELINE_H
    #include "pipeline/Pipeline.hpp"
    #define PIPELINE_H
#endif

class GLSL_Flatscape : public GLSL_Base {
public:
    GLSL_Flatscape(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
        GLSL_Flatscape::shaderProgID = compileShaders(vertexShaderFilePath, fragmentShaderFilePath);
        glUseProgram(GLSL_Flatscape::shaderProgID);
        initUniforms();
    }
    enum unifID { mvpMatrix, renderMode };
    void set_mvpMatrix(glm::mat4 mvpMatrix);
    void set_renderMode(GLuint renderMode);
private:
    GLuint unifLoc[2];
    void initUniforms();
};