
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
// #include "LoadTextures.h"

/* Handles main OpenGL functionality */

const std::string getParentDirectory(const char* path) {
    const char* ptr = path + strlen(path);
    while (ptr != path && nullptr == strchr("\\/", *(--ptr)));
    std::size_t len = ptr - path;
    std::string result(path, len);
    std::cout << "Parent dir: " << result << std::endl;
    return result;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int argc, const char* argv[]){

    system("COLOR 0A");
    glEnable(GL_DEPTH_TEST);
    int width, height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
    GLuint shaderProg3 = compileShaders(parentDir, "AO-4.vert", "AO-3.frag");
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

    std::cout << "result: " << glGetError() << std::endl;

    GLuint VBO, VAO, EBO;
    GLuint VBOs[2];
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(2, VBOs);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts3), verts3, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat)  , (GLvoid*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    // Task: Make sure variable at layout (location = ...) exists, otherwise yield error message
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    // glVertexAttribIPointer(1, 4, GL_UNSIGNED_BYTE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1); // h

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices5), indices5, GL_STATIC_DRAW);

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
        Projection = glm::translate(Projection, glm::vec3(0.2f, -0.2f, 0.0f));
        Projection = glm::scale(Projection, glm::vec3(-0.4, -0.4, 0.0f));
        Projection = glm::rotate(Projection, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        glUniformMatrix4fv(Projection_loc, 1, GL_FALSE, glm::value_ptr(Projection));

        glDrawElements(GL_TRIANGLES, sizeof(indices5) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    system("COLOR 0F");
    return 0;
}
