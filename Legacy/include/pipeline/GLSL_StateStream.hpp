#ifndef PIPELINE_H
    #include "pipeline/Pipeline.hpp"
    #define PIPELINE_H
#endif

class GLSL_StateStream : public GLSL_Base {
public:
    GLSL_StateStream(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
        GLSL_StateStream::shaderProgID = compileShaders(vertexShaderFilePath, fragmentShaderFilePath);
        glUseProgram(GLSL_StateStream::shaderProgID);
        initUniforms();
    }
    enum unifID { mvpMatrix };
    void set_mvpMatrix(glm::mat4 mvpMatrix);
private:
    GLuint unifLoc[1];
    void initUniforms();
};
