#ifndef PIPELINE_H
    #include "Pipeline.hpp"
    #define PIPELINE_H
#endif

#include "Feeds.h"

#ifndef PIPELINE_TILEMAP_H
    class GLSL_Tilemap : public GLSL_Base {
    public:
        GLSL_Tilemap(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
            GLSL_Tilemap::shaderProgID = compileShaders(vertexShaderFilePath, fragmentShaderFilePath);
            glUseProgram(GLSL_Tilemap::shaderProgID);
            initUniforms();
        }
        enum unifID { mvpMatrix, state };
        void set_mvpMatrix(glm::mat4 mvpMatrix);
        void set_state(GLint state);
    private:
        GLuint inputFeeds[1] = { FEED_POS_ID };
        GLuint unifLoc[2];
        void initUniforms();
    };
#define PIPELINE_TILEMAP_H
#endif
