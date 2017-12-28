#ifndef PIPELINE_H
    #include "Pipeline.hpp"
    #define PIPELINE_H
#endif

#include "Feeds.h"

#ifndef PIPELINE_IDLE_H
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
        GLuint inputFeeds[2] = { 
            FEED_POS_ID, 
            FEED_STATE_ID
        };
        GLuint unifLoc[2];
        void initUniforms();
    };
#define PIPELINE_IDLE_H
#endif
