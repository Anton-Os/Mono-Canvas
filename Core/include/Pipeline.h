#include <iostream>
#include <array>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Loaders.h"

class GLSL_Base {
public:
    GLuint shaderProgID;
};

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

