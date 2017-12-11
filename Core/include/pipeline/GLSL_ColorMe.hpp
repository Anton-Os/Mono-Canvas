#ifndef PIPELINE_H
    #include "Pipeline.hpp"
    #define PIPELINE_H
#endif

#ifndef PIPELINE_COLOR_ME_H
    class GLSL_ColorMe : public GLSL_Base {
    public:
        GLSL_ColorMe(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
            GLSL_ColorMe::shaderProgID = compileShaders(vertexShaderFilePath, fragmentShaderFilePath);
            glUseProgram(GLSL_ColorMe::shaderProgID);
            initUniforms();
        }
        enum unifID { mvpMatrix, renderMode, xMin, xMax, yMin, yMax, zMin, zMax };
        void set_mvpMatrix(glm::mat4 mvpMatrix);
        void set_renderMode(GLuint renderMode);
        void set_xMin(float xMin);
        void set_xMax(float xMin);
        void set_yMin(float xMin);
        void set_yMax(float xMin);
        void set_zMin(float xMin);
        void set_zMax(float xMin);
    private:
        GLuint unifLoc[8];
        void initUniforms();
    };
#define PIPELINE_COLOR_ME_H
#endif
