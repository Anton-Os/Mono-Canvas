
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    GLuint shaderProg3 = compileShaders(parentDir, "AO-3.vert", "AO-3.frag");
    glUseProgram(shaderProg3);
    // result = glGetError();
    // GLuint shaderProg = initLoadShaders();

    // const char* absoluteKTX1 = "D:\\AntonDocs\\Codex\\Mono-Canvas\\MinGW-64-V3\\AO\\AO-Projects\\Learning\\Textures\\KTX\\Container.KTX";
    // const char* absoluteKTX2 = "D:\\AntonDocs\\Codex\\Mono-Canvas\\Git-Mingw-64\\AO\\AO\\Learning\\data\\ktx\\Metal-1.ktx";
    // GLuint myTexture = produceTexture2(absoluteKTX);
    /* std::string fileKTX = "\\data\\ktx\\Texture8_PNG_BC7_1.KTX";
    std::string pathKTX = parentDir + fileKTX;
    const char* c_pathKTX = pathKTX.c_str();
    std::cout << "Relative path to KTX file is " << pathKTX << std::endl;
    GLuint myTexture = createTexture(c_pathKTX);
    // result = glGetError();
    if(myTexture == 0){
        std::cerr << "Errors occured producing texture" << std::endl;
        return 1;
    } else {
        std::cout << "Texture created successfuly from file: \n" << c_pathKTX << std::endl;
    } */

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
        // 1, 6, 11,
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices4), indices4, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinding
    glBindVertexArray(0); // Unbinding
    int cnt = 0;
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 0.88, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 9);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, sizeof(indices4) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    system("COLOR 0F");
    return 0;
}
