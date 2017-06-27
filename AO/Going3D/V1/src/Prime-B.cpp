
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
GLfloat rotateZ = 0;

const std::string getParentDirectory(const char* path) {
    const char* ptr = path + strlen(path);
    while (ptr != path && nullptr == strchr("\\/", *(--ptr)));
    std::size_t len = ptr - path;
    std::string result(path, len);
    std::cout << "Parent dir: " << result << std::endl;
    return result;
}

/* void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if(key == GLFW_KEY_Q && action == GLFW_REPEAT){
        scaleX += 0.1;
        scaleY += 0.1;
        std::cout << "scaleX set to: " << scaleX << std::endl;
        std::cout << "scaleX set to: " << scaleY << std::endl;
    }
    if(key == GLFW_KEY_E && action == GLFW_REPEAT){
        scaleX -= 0.1;
        scaleY -= 0.1;
        std::cout << "scaleX set to: " << scaleX << std::endl;
        std::cout << "scaleX set to: " << scaleY << std::endl;
    }
    if(key == GLFW_KEY_W && action == GLFW_REPEAT){
        moveY += 0.1;
        std::cout << "moveY set to: " << moveY << std::endl;
    }
    if(key == GLFW_KEY_S && action == GLFW_REPEAT){
        moveY -= 0.1;
        std::cout << "moveY set to: " << moveY << std::endl;
    }
    if(key == GLFW_KEY_D && action == GLFW_REPEAT){
        moveX += 0.1;
        std::cout << "moveX set to: " << moveX << std::endl;
    }
    if(key == GLFW_KEY_A && action == GLFW_REPEAT){
        moveX -= 0.1;
        std::cout << "moveX set to: " << moveX << std::endl;
    }
    if(key == GLFW_KEY_F && action == GLFW_REPEAT){
        timeAngle += 0.1;
        std::cout << "timeAngle set to: " << timeAngle << std::endl;
    }
    if(key == GLFW_KEY_R && action == GLFW_REPEAT){
        if(timeAngle == 0){
            std::cout << "timeAngle is at zero and cannot decrease further" << timeAngle << std::endl;
        } else {
            timeAngle -= 0.1;
        }
        std::cout << "timeAngle set to: " << timeAngle << std::endl;
    }
    if(key == GLFW_KEY_Y && action == GLFW_REPEAT){
        rotateX += 0.1;
        std::cout << "rotateX set to: " << rotateX << std::endl;
    }
    if(key == GLFW_KEY_U && action == GLFW_REPEAT){
        rotateX -= 0.1;
        std::cout << "rotateX set to: " << rotateX << std::endl;
    }
    if(key == GLFW_KEY_H && action == GLFW_REPEAT){
        rotateY += 0.1;
        std::cout << "rotateY set to: " << rotateY << std::endl;
    }
    if(key == GLFW_KEY_J && action == GLFW_REPEAT){
        rotateY -= 0.1;
        std::cout << "rotateY set to: " << rotateY << std::endl;
    }
    if(key == GLFW_KEY_N && action == GLFW_REPEAT){
        rotateZ += 0.1;
        std::cout << "rotateZ set to: " << rotateZ << std::endl;
    }
    if(key == GLFW_KEY_M && action == GLFW_REPEAT){
        rotateZ -= 0.1;
        std::cout << "rotateZ set to: " << rotateZ << std::endl;
    }
    if(key == GLFW_KEY_P && action == GLFW_REPEAT){
        timeAngle = 1;
        rotateX = 0;
        rotateY = 0;
        rotateZ = 0;
    }
} */

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if(key == GLFW_KEY_Q && action == GLFW_REPEAT){
        scaleX += 0.1;
        scaleY += 0.1;
    }
    if(key == GLFW_KEY_E && action == GLFW_REPEAT){
        scaleX -= 0.1;
        scaleY -= 0.1;
    }
    if(key == GLFW_KEY_W && action == GLFW_REPEAT){
        moveY += 0.1;
    }
    if(key == GLFW_KEY_S && action == GLFW_REPEAT){
        moveY -= 0.1;
    }
    if(key == GLFW_KEY_D && action == GLFW_REPEAT){
        moveX += 0.1;
    }
    if(key == GLFW_KEY_A && action == GLFW_REPEAT){
        moveX -= 0.1;
    }
    if(key == GLFW_KEY_F && action == GLFW_REPEAT){
        timeAngle += 0.1;
    }
    if(key == GLFW_KEY_R && action == GLFW_REPEAT){
        if(timeAngle == 0){
            std::cout << "timeAngle is at zero and cannot decrease further" << timeAngle << std::endl;
        } else {
            timeAngle -= 0.1;
        }
    }
    if(key == GLFW_KEY_Y && action == GLFW_REPEAT){
        rotateX += 0.1;
    }
    if(key == GLFW_KEY_U && action == GLFW_REPEAT){
        rotateX -= 0.1;
    }
    if(key == GLFW_KEY_H && action == GLFW_REPEAT){
        rotateY += 0.1;
    }
    if(key == GLFW_KEY_J && action == GLFW_REPEAT){
        rotateY -= 0.1;
    }
    if(key == GLFW_KEY_N && action == GLFW_REPEAT){
        rotateZ += 0.1;
    }
    if(key == GLFW_KEY_M && action == GLFW_REPEAT){
        rotateZ -= 0.1;
    }
    if(key == GLFW_KEY_P && action == GLFW_REPEAT){
        timeAngle = 1;
        rotateX = 0;
        rotateY = 0;
        rotateZ = 0;
    }
}

int main(int argc, const char* argv[]){

    system("COLOR 0A");
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glEnable(GL_DEPTH_TEST);
    int width, height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Mono-Canvas", nullptr, nullptr);
    if(nullptr == window){
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    // GLenum result = glGetError();

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, &keyCallback);
    std::string parentDir(getParentDirectory(argv[0]));
    GLuint shaderProg1 = compileShaders(parentDir, "AO-1.vert", "AO-1.frag");
    GLuint shaderProg2 = compileShaders(parentDir, "AO-2.vert", "AO-2.frag");
    GLuint shaderProg3 = compileShaders(parentDir, "AO-3.vert", "AO-3.frag");
    glUseProgram(shaderProg3);

    struct Vertex {
        GLfloat pos[3];
        GLubyte color[4];
    };

    Vertex verts[] = {
        { {0.5f, 0.5f, 0},
          {255, 0, 0, 255} },
        { {0.5f, -0.5f, 0},
          {255, 0, 0, 255} },
        { {-0.5f, -0.5f, 0},
          {255, 0, 0, 255} },
        { {-0.5f,  0.5f, 0},
          {0, 0, 255, 255} },
        { {0.9f, 0.9f, 0},
          {0, 0, 255, 255} },
        { {0.8f, 0.5f, 0},
          {0, 0, 255, 255} },
        { {-0.3f, 0.3f, 0},
          {206, 66, 244, 255} },
        { {-1.0f, 0.3f, 0},
          {206, 66, 244, 255} },
        { {-0.3f, -0.4f, 0},
          {206, 66, 244, 255} }
    };

    Vertex verts2[] = {
        { {1.0f, 1.0f, 0},
          {255, 0, 0, 255} },
        { {1.0f, -1.0f, 0},
          {255, 0, 0, 255} },
        { {-1.0f, -1.0f, 0},
          {255, 0, 0, 255} },
        { {-1.0f,  1.0f, 0},
          {255, 0, 255, 255} }
    };

    Vertex verts3[] = {
        { {0.7f, 0.5f, 0}, {63, 127, 191, 255} }, // INDEX 0
        { {0.7f, -0.5f, 0}, {219, 97, 99, 255} }, // INDEX 1
        { {-0.7f, 0.9f, 0}, {126, 251, 138, 255} }, // INDEX 2
        { {-0.7f, -0.9f, 0}, {178, 137, 204, 255} }, // INDEX 3

        { {0.5f, 0.7f, 0}, {63, 127, 191, 255} }, // INDEX 0
        { {0.5f, -0.7f, 0}, {219, 97, 99, 255} }, // INDEX 1
        { {-0.5f, 0.9f, 0}, {126, 251, 138, 255} }, // INDEX 2
        { {-0.5f, -0.9f, 0}, {178, 137, 204, 255} }, // INDEX 3

        { {0.9f, 0.5f, 0}, {63, 127, 191, 255} }, // INDEX 0
        { {0.9f, -0.5f, 0}, {219, 97, 99, 255} }, // INDEX 1
        { {-0.9f, 0.5f, 0}, {126, 251, 138, 255} }, // INDEX 2
        { {-0.9f, -0.5f, 0}, {178, 137, 204, 255} }, // INDEX 3
    };

    /* Vertex verts3[] = {
        {{ 1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ 1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},

        {{ 1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ 1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},

        {{ 1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ 1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},

        {{ 1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ 1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},

        {{ 1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ 1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},

        {{ 1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f, 1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ 1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},
        {{ -1.0f,-1.0f, 1.0f }, { 255, 0, 0, 255 }},

           1.0f, 1.0f, 1.0f,       0.0f, 1.0f, 0.0f, // vertex 0
           1.0f,-1.0f, 1.0f,       0.0f, 1.0f, 0.0f, // vertex 1
           1.0f, 1.0f,-1.0f,       0.0f, 1.0f, 0.0f, // vertex 2
           1.0f,-1.0f,-1.0f,       0.0f, 1.0f, 0.0f, // vertex 3

           1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 1.0f, // vertex 0
           1.0f, 1.0f,-1.0f,       0.0f, 0.0f, 1.0f, // vertex 1
          -1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 1.0f, // vertex 2
          -1.0f, 1.0f,-1.0f,       0.0f, 0.0f, 1.0f, // vertex 3

           1.0f, 1.0f,-1.0f,       1.0f, 1.0f, 0.0f, // vertex 0
           1.0f,-1.0f,-1.0f,       1.0f, 1.0f, 0.0f, // vertex 1
          -1.0f, 1.0f,-1.0f,       1.0f, 1.0f, 0.0f, // vertex 2
          -1.0f,-1.0f,-1.0f,       1.0f, 1.0f, 0.0f, // vertex 3

          -1.0f, 1.0f, 1.0f,       0.0f, 1.0f, 1.0f, // vertex 0
          -1.0f, 1.0f,-1.0f,       0.0f, 1.0f, 1.0f, // vertex 1
          -1.0f,-1.0f, 1.0f,       0.0f, 1.0f, 1.0f, // vertex 2
          -1.0f,-1.0f,-1.0f,       0.0f, 1.0f, 1.0f, // vertex 3

           1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 1.0f, // vertex 0
          -1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 1.0f, // vertex 1
           1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 1.0f, // vertex 2
          -1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 1.0f, // vertex 3
    }; */

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

    GLuint indices[] = {
        0, 1, 3,
        4, 5, 0
    };

    GLuint indices2[] = {
        0, 1, 3,
        2, 1, 3
    };

    GLuint indices3[] = {
        0, 5 + 3, 10,
        // 1, 6, 11,l
        5, 7, 8,
        // 3, 4, 9
    };

    GLuint indices4[] = {
        // 5, 7, 8,
        0, 4, 8,
        0 + 1, 4 + 1, 8 + 1,
        0 + 2, 4 + 2, 8 + 2,
        0 + 3, 4 + 3, 8 + 3
    };

    GLuint indices5[] = {
        0, 1, 3,
        2, 1, 3,
        // 11, 6, 8
    };

    GLuint boxishIndices[] = {
        5, 6, 7,
        8, 9, 10,
        11, 12, 13,
        14, 15, 16
    };

    std::cout << "result: " << glGetError() << std::endl;

    GLuint VBO, VAO, EBO;
    GLuint VBOs[2];
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(2, VBOs);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boxishShape), boxishShape, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxishIndices), boxishIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinding
    glBindVertexArray(0); // Unbinding

    GLint Projection_loc = glGetUniformLocation(shaderProg3, "Projection");

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 0.88, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 9);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        float t = glfwGetTime();

        /* glm::mat4 Projection = glm::perspective(90.0f, 4.0f / 3.0f, 0.1f, 100.f);
        glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.5f));
        View = glm::rotate(View, 5.0f*t, glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 ViewProjection = Projection*View;
        glUniformMatrix4fv(ViewProjection_loc, 1, GL_FALSE, glm::value_ptr(ViewProjection)); */

        glm::mat4 Projection;
        Projection = glm::translate(Projection, glm::vec3(moveX, moveY, 0.0f));
        Projection = glm::scale(Projection, glm::vec3(scaleX, scaleY, 0.0f));
        Projection = glm::rotate(Projection, (float)glfwGetTime() * timeAngle, glm::vec3(rotateX, rotateY, rotateZ));
        // Projection = glm::rotate(Projection, (float)glfwGetTime() * 2, -0.5f, 0.0f, 0.0f);
        glUniformMatrix4fv(Projection_loc, 1, GL_FALSE, glm::value_ptr(Projection));

        glDrawElements(GL_TRIANGLES, sizeof(boxishIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    system("COLOR 0F");
    return 0;
}
