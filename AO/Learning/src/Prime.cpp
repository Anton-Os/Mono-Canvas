
#include <iostream>
#include <cmath>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "LoadShaders.h"
#include "TexturesGL.h"

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

    system("COLOR F0");
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

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, &keyCallback);
    std::string parentDir(getParentDirectory(argv[0]));
    GLuint shaderProg = compileShaders(parentDir, "Mono1.vert", "Mono1.frag");
    glUseProgram(shaderProg);
    // GLuint shaderProg = initLoadShaders();

    // const char* absoluteKTX = "D:/AntonDocs/Codex/Mono-Canvas/MinGW-64-V2/MyDev/AO-Projects/Learning/Metal1/Metal1.ktx";
    // const char* absoluteKTX = "D:\\AntonDocs\\Codex\\Mono-Canvas\\MinGW-64-V2\\MyDev\\AO-Projects\\Learning\\Textures\\KTX\\Metal\\Metal1.ktx";
    // const char* absoluteKTX_bug = "D:\\AntonDocs\\Codex\\Mono-Canvas\\MinGW-64-V3\\MyDev\\AO-Projects\\Learning\\Textures\\KTX\\Container\\Container.KTX";
    const char* absoluteKTX = "D:\\AntonDocs\\Codex\\Mono-Canvas\\MinGW-64-V3\\AO\\AO-Projects\\Learning\\Textures\\KTX\\Container.KTX";
    // GLuint myTexture = produceTexture2(absoluteKTX);
    GLuint myTexture = createTexture(absoluteKTX);
    if(myTexture == 0){
        std::cout << "Errors occured producing texture" << std::endl;
        return -1;
    }

    struct MyVert {
        GLfloat pos[3];
        GLubyte color[4];
    };

    MyVert verts[] = {
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

    GLfloat textureCoord[] = {
        0.5f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3,
        4, 5, 0
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(coord), coord, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVert), (GLvoid*)offsetof(MyVert, pos));
    glEnableVertexAttribArray(0);
    // Task: Make sure variable at layout (location = ...) exists, otherwise yield error message

    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(MyVert), (GLvoid*)offsetof(MyVert, color));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinding
    glBindVertexArray(0); // Unbinding

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 0.88, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 9);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}
