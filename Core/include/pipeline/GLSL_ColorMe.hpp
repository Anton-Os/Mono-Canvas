#ifndef PIPELINE_H
    #include "Pipeline.hpp"
    #define PIPELINE_H
#endif

#include "Feeds.h"

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
        void set_xMin(GLfloat xMin);
        void set_xMax(GLfloat xMax);
        void set_yMin(GLfloat yMin);
        void set_yMax(GLfloat yMax);
        void set_zMin(GLfloat zMin);
        void set_zMax(GLfloat zMax);
    private:
        GLuint inputFeeds[1] = { FEED_POS_ID };
        GLuint unifLoc[8];
        void initUniforms();
    };
#define PIPELINE_COLOR_ME_H
#endif
