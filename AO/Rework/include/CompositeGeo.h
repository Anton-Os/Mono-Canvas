#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GL4_Sphere {
public:
    GL4_Sphere(GLuint radius, GLuint sliceCount, GLuint stackCount){
        create(radius, sliceCount, stackCount);
    }
    std::vector<GLuint> feed;
    glm::mat4 relMatrix;
    void create(GLuint radius, GLuint sliceCount, GLuint stackCount);
    void draw();
    void draw(GLenum drawMode);
    // void drawTimed(std::chrono::duration<int, std::milli> currTime, GLuint speedPer100);
    void drawFixed(GLenum drawMode, GLuint indexCount);
    void drawPart(GLuint part, GLuint whole);
private:
    GLuint vertexCount;
};