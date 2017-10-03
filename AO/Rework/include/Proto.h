#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
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
private:
    GLuint indexCount;
};