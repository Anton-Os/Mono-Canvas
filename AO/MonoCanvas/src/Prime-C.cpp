
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Common.h"

GLfloat scaleX = 1.0f;
GLfloat scaleY = 1.0f;
GLfloat moveX = 0;
GLfloat moveY = 0;
GLfloat timeAngle = 0.0f;
GLfloat rotateX = 0;
GLfloat rotateY = 0;
GLfloat rotateZ = 1.0;

GLboolean Q, W, E, R, Y, U, P, A, S, D, F, H, J, N, M = false;

const std::string getParentDirectory(const char* path) {
    const char* ptr = path + strlen(path);
    while (ptr != path && nullptr == strchr("\\/", *(--ptr)));
    std::size_t len = ptr - path;
    std::string result(path, len);
    std::cout << "Parent dir: " << result << std::endl;
    return result;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);

    if(key == GLFW_KEY_Q && action == GLFW_PRESS) Q = true;
    if(key == GLFW_KEY_E && action == GLFW_PRESS) E = true;
    if(key == GLFW_KEY_W && action == GLFW_PRESS) W = true;
    if(key == GLFW_KEY_S && action == GLFW_PRESS) S = true;
    if(key == GLFW_KEY_D && action == GLFW_PRESS) D = true;
    if(key == GLFW_KEY_A && action == GLFW_PRESS) A = true;
    if(key == GLFW_KEY_F && action == GLFW_PRESS) F = true;
    if(key == GLFW_KEY_R && action == GLFW_PRESS) R = true;
    if(key == GLFW_KEY_Y && action == GLFW_PRESS) Y = true;
    if(key == GLFW_KEY_U && action == GLFW_PRESS) U = true;
    if(key == GLFW_KEY_H && action == GLFW_PRESS) H = true;
    if(key == GLFW_KEY_J && action == GLFW_PRESS) J = true;
    if(key == GLFW_KEY_N && action == GLFW_PRESS) N = true;
    if(key == GLFW_KEY_M && action == GLFW_PRESS) M = true;
    if(key == GLFW_KEY_P && action == GLFW_PRESS) P = true;

    if(key == GLFW_KEY_Q && action == GLFW_RELEASE) Q = false;
    if(key == GLFW_KEY_E && action == GLFW_RELEASE) E = false;
    if(key == GLFW_KEY_W && action == GLFW_RELEASE) W = false;
    if(key == GLFW_KEY_S && action == GLFW_RELEASE) S = false;
    if(key == GLFW_KEY_D && action == GLFW_RELEASE) D = false;
    if(key == GLFW_KEY_A && action == GLFW_RELEASE) A = false;
    if(key == GLFW_KEY_F && action == GLFW_RELEASE) F = false;
    if(key == GLFW_KEY_R && action == GLFW_RELEASE) R = false;
    if(key == GLFW_KEY_Y && action == GLFW_RELEASE) Y = false;
    if(key == GLFW_KEY_U && action == GLFW_RELEASE) U = false;
    if(key == GLFW_KEY_H && action == GLFW_RELEASE) H = false;
    if(key == GLFW_KEY_J && action == GLFW_RELEASE) J = false;
    if(key == GLFW_KEY_N && action == GLFW_RELEASE) N = false;
    if(key == GLFW_KEY_M && action == GLFW_RELEASE) M = false;
    if(key == GLFW_KEY_P && action == GLFW_RELEASE) P = false;

    if(Q){ scaleX += 0.03; scaleY += 0.03; }
    if(E){ scaleX -= 0.03; scaleY -= 0.03; }
    if(W){ moveY += 0.03; }
    if(S){ moveY -= 0.03; }
    if(D){ moveX += 0.03; }
    if(A){ moveX -= 0.03; }
    if(F){ timeAngle += 0.03; }
    if(R){
        if(timeAngle > 0){ timeAngle -= 0.03; }
    }
    if(Y){ rotateX += 0.03; }
    if(U){ rotateX -= 0.03; }
    if(H){ rotateY += 0.03; }
    if(J){ rotateY -= 0.03; }
    if(N){ rotateZ += 0.03; }
    if(M){ rotateZ -= 0.03; }
    if(P){
        timeAngle = 1;
        rotateX = 0;
        rotateY = 0;
        rotateZ = 0;
    }
}

int main(int argc, const char* argv[]){

    system("COLOR 0A");
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    int width, height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glViewport(0, 0, width, height);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Mono-Canvas", nullptr, nullptr);
    if(nullptr == window){
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &width, &height);
    // GLenum result = glGetError();

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);

    glfwSetKeyCallback(window, &keyCallback);
    std::string parentDir(getParentDirectory(argv[0]));
    GLuint shaderProg = compileShaders(parentDir, "AO-5.vert", "AO-5.frag");
    glUseProgram(shaderProg);
    // result = glGetError();

    std::string fileKTX1 = "\\data\\ktx\\spotted-steel_PNG_BC7_3.KTX";
    std::string fileKTX2 = "\\data\\ktx\\800px-Birnam_wood_macbeth_PNG_BC7_1.KTX";
    std::string fileKTX3 = "\\data\\ktx\\wildtextures-creased-white-paper-texture_PNG_BC7_1.KTX";
    std::string fileKTX4 = "\\data\\ktx\\Texture8_PNG_BC7_1.KTX";
    std::string pathKTX1 = parentDir + fileKTX1;
    std::string pathKTX2 = parentDir + fileKTX2;
    std::string pathKTX3 = parentDir + fileKTX3;
    std::string pathKTX4 = parentDir + fileKTX4;
    // const char* c_pathKTX = pathKTX.c_str();
    // std::cout << "Relative path to KTX file is " << pathKTX << std::endl;
    GLuint texture1 = createTexture(pathKTX1.c_str());
    textureCheck(texture1, pathKTX1);
    GLuint texture2 = createTexture(pathKTX2.c_str());
    textureCheck(texture2, pathKTX2);
    GLuint texture3 = createTexture(pathKTX3.c_str());
    textureCheck(texture3, pathKTX3);
    GLuint texture4 = createTexture(pathKTX4.c_str());
    textureCheck(texture4, pathKTX4);

    struct Vertex {
        GLfloat pos[3];
        GLubyte color[4];
    };

    Vertex verts[] = {
        { {1.0f / 2, 1.0f / 2, 0},
          {255, 0, 0, 255} },
        { {1.0f / 2 + 0.2f, -1.0f / 2, 0},
          {255, 0, 0, 255} },
        { {-1.0f / 2, -1.0f / 2, 0},
          {255, 0, 0, 255} },
        { {-1.0f / 2 - 0.2f,  1.0f / 2, 0},
          {255, 0, 255, 255} }
    };

    Vertex boxishShape[] = {
        // REFERENCE
        { {0.0f, 0.0, 0.0}, {40, 40, 40, 255} },
        { {0.5f, 0.5f, 0.0}, {40, 40, 40, 255} },
        { {-0.5f, 0.5f, 0.0}, {40, 40, 40, 255} },
        { {0.5f, -0.5f, 0.0}, {40, 40, 40, 255} },
        { {-0.5f, -0.5f, 0.0}, {40, 40, 40, 255} },
        // TOP TRIANGLE
        { {0.0f, 0.0f + 0.02f, 0.0}, {63, 127, 191, 255} },
        { {0.5f, 0.5f + 0.02f, 0.0}, {63, 127, 191, 255} },
        { {-0.5f, 0.5f + 0.02f, 0.0}, {63, 127, 191, 255} },
        // RIGHT TRIANGLE
        { {0.0f + 0.02f, 0.0, 0.0}, {219, 97, 99, 255} },
        { {0.5f + 0.02f, 0.5f, 0.0}, {219, 97, 99, 255} },
        { {0.5f + 0.02f, -0.5f, 0.0}, {219, 97, 99, 255} },
        // BOTTOM TRIANGLE
        { {0.0f, 0.0 - 0.02f, 0.0}, {126, 251, 138, 255} },
        { {0.5f, -0.5f - 0.02f, 0.0}, {126, 251, 138, 255} },
        { {-0.5f, -0.5f - 0.02f, 0.0}, {126, 251, 138, 255} },
        // LEFT TRIANGLE
        { {0.0f - 0.02f, 0.0}, {178, 137, 204, 255} },
        { {-0.5f - 0.02f, 0.5f, 0.0}, {178, 137, 204, 255} },
        { {-0.5f - 0.02f, -0.5f, 0.0}, {178, 137, 204, 255} },
    };

    Vertex sixFaceCube[] = {
        {{ 1.0f, 1.0f, 1.0f }, { 63, 127, 191, 255 }},
        {{ -1.0f, 1.0f, 1.0f }, { 63, 127, 191, 255 }},
        {{ 1.0f, -1.0f, 1.0f }, { 63, 127, 191, 255 }},
        {{ -1.0f, -1.0f, 1.0f }, { 63, 127, 191, 255 }},

        {{ 1.0f, 1.0f, 1.0f }, { 219, 97, 99, 255 }},
        {{ 1.0f, -1.0f, 1.0f }, { 219, 97, 99, 255 }},
        {{ 1.0f, 1.0f, -1.0f }, { 219, 97, 99, 255 }},
        {{ 1.0f, -1.0f, -1.0f }, { 219, 97, 99, 255 }},

        {{ 1.0f, 1.0f, 1.0f }, { 126, 251, 138, 255 }},
        {{ 1.0f, 1.0f, -1.0f }, { 126, 251, 138, 255 }},
        {{ -1.0f, 1.0f, 1.0f }, { 126, 251, 138, 255 }},
        {{ -1.0f, 1.0f, -1.0f }, { 126, 251, 138, 255 }},

        {{ 1.0f, -1.0f, 1.0f }, { 0, 255, 204, 255 }},
        {{ -1.0f, -1.0f, 1.0f }, { 0, 255, 204, 255 }},
        {{ 1.0f, -1.0, -1.0f }, { 0, 255, 204, 255 }},
        {{ -1.0f, -1.0f, -1.0f }, {  0, 255, 204, 255 }},

        {{ 1.0f, 1.0f, -1.0f }, { 178, 137, 204, 255 }},
        {{ 1.0f, -1.0f, -1.0f }, { 178, 137, 204, 255 }},
        {{ -1.0f, 1.0f, -1.0f }, { 178, 137, 204, 255 }},
        {{ -1.0f, -1.0f, -1.0f }, { 178, 137, 204, 255 }},

        {{ -1.0f, 1.0f, 1.0f }, { 235, 163, 137, 255 }},
        {{ -1.0f, 1.0f,-1.0f }, { 235, 163, 137, 255 }},
        {{ -1.0f,-1.0f, 1.0f }, { 235, 163, 137, 255 }},
        {{ -1.0f,-1.0f,-1.0f }, { 235, 163, 137, 255 }}
    };

    GLfloat texCoord[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f
    };

    GLfloat texCoord2[] = {
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        0.5f, 0.5f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.5f, 0.5f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.5f, 0.5f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.5f, 0.5f,
        0.0f, 1.0f,
        0.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 3,
        2, 1, 3
    };

    GLuint boxishIndices[] = {
        5, 6, 7,
        8, 9, 10,
        11, 12, 13,
        14, 15, 16
    };

    GLuint cubeIndices[] = {
        0,1,2,
        2,1,3,
        4,5,6,
        6,5,7,
        8,9,10,
        10,9,11,
        12,13,14,
        14,13,15,
        16,17,18,
        18,17,19,
        20,21,22,
        22,21,23,
    };

    GLuint VBO, VAO, EBO;
    GLuint VBOs[100];
    GLuint EBOs[10];
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(100, VBOs);
    glGenBuffers(10, EBOs);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord2), texCoord2, GL_STATIC_DRAW);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxishShape), boxishShape, GL_STATIC_DRAW);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(4);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sixFaceCube), sixFaceCube, GL_STATIC_DRAW);

    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(6, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(6);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxishIndices), boxishIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinding
    glBindVertexArray(0); // Unbinding

    GLint Projection_loc = glGetUniformLocation(shaderProg, "Projection");
    GLint View_loc = glGetUniformLocation(shaderProg, "View");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 0.88, 1.0f);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProg);
        glBindVertexArray(VAO);
        float t = glfwGetTime();
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
        glm::mat4 View(1);

        View = glm::translate(glm::mat4(1), glm::vec3(moveX, moveY, -4.0f));
        View = glm::scale(View, glm::vec3(scaleX, scaleY, 0.0f));
        View = glm::rotate(View, t * timeAngle, glm::vec3(rotateX, rotateY, rotateZ));

        glUniformMatrix4fv(Projection_loc, 1, GL_FALSE, glm::value_ptr(Projection));
        glUniformMatrix4fv(View_loc, 1, GL_FALSE, glm::value_ptr(View));

        glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    system("COLOR 0F");
    return 0;
}
