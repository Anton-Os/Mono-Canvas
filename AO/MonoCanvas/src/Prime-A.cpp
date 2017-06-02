
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Common.h>

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
    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // GLFWwindow* window = glfwCreateWindow(800, 600, "Mono-Canvas", nullptr, nullptr);
    GLFWwindow* window = glfwCreateWindow(800 * 2, 600 * 2, "Mono-Canvas", nullptr, nullptr);
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
    glUseProgram(shaderProg2);
    // result = glGetError();

    std::string fileKTX1 = "\\data\\ktx\\Texture8_PNG_BC7_1.KTX";
    std::string fileKTX2 = "\\data\\ktx\\800px-Birnam_wood_macbeth_PNG_BC7_1.KTX";
    std::string fileKTX3 = "\\data\\ktx\\spotted-steel_PNG_BC7_3.KTX";
    std::string fileKTX4 = "\\data\\ktx\\wildtextures-creased-white-paper-texture_PNG_BC7_1.KTX";
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
    /* GLuint texture3 = createTexture(pathKTX3.c_str());
    textureCheck(texture3, pathKTX3); */
    GLuint texture4 = createTexture(pathKTX4.c_str());
    textureCheck(texture4, pathKTX4);
    GLuint texture3 = createTexture(pathKTX3.c_str());
    textureCheck(texture3, pathKTX3);

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
        { {1.0f, 1.0f, 0}, {20, 0, 0, 255} },
        { {0.55f, 1.0f, 0}, {0, 20, 0, 255} },
        { {1.0f, 0.55f, 0}, {0, 0, 20, 255} },

        { {-1.0f, 1.0f, 0}, {20, 0, 0, 255} },
        { {-0.55f, 1.0f, 0}, {0, 20, 0, 255} },
        { {-1.0f, 0.55f, 0}, {0, 0, 20, 255} },

        { {1.0f, -1.0f, 0}, {20, 0, 0, 255} },
        { {0.55f, -1.0f, 0}, {0, 20, 0, 255} },
        { {1.0f, -0.55f, 0}, {0, 0, 20, 255} },

        { {-1.0f, -1.0f, 0}, {20, 0, 0, 255} },
        { {-0.55f, -1.0f, 0}, {0, 20, 0, 255} },
        { {-1.0f, -0.55f, 0}, {0, 0, 20, 255} },
    };

    Vertex verts4[] = {
        { {1.0f / 2, 1.0f / 2, 0},
          {255, 0, 0, 255} },
        { {1.0f / 2 + 0.2f, -1.0f / 2, 0},
          {255, 0, 0, 255} },
        { {-1.0f / 2, -1.0f / 2, 0},
          {255, 0, 0, 255} },
        { {-1.0f / 2 - 0.2f,  1.0f / 2, 0},
          {255, 0, 255, 255} }
    };


    /* GLfloat texCoord[] = {
        0.75f, 0.75f,
        0.75f, 0.25f,
        0.25f, 0.75f
    }; */

    /* GLfloat texCoord[] = {
        0.75f / 3, 0.75f / 3,
        0.75f / 3, 0.25f / 3,
        0.25f / 3, 0.75f / 3
    }; */

    /* GLfloat texCoord[] = {
        0.75f * 1.5, 0.75f * 1.5,
        0.75f * 1.5, 0.25f * 1.5,
        0.25f * 1.5, 0.75f * 1.5
    }; */

    GLfloat texCoord[] = {
        0.75f * 2, 0.75f * 2,
        0.75f * 2, 0.25f * 2,
        0.25f * 2, 0.75f * 2
    };

    GLfloat texCoord2[] = {
        1.0f * 2, 1.0f * 2,
        1.0f * 2, 0.0f * 2,
        0.0f * 2, 1.0f * 2
    };

    GLuint indices[] = {
        0, 1, 3,
        4, 5, 0
    };

    GLuint indices2[] = {
        0, 1, 3,
        2, 1, 3
    };

    GLuint VBO, VAO, EBO;
    GLuint VBOs[2];
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(2, VBOs);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(verts2), verts2, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts4), verts4, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat)  , (GLvoid*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    // Task: Make sure variable at layout (location = ...) exists, otherwise yield error message
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord2), texCoord2, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinding
    glBindVertexArray(0); // Unbinding

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 0.88, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 9);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, sizeof(indices2) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    system("COLOR 0F");
    return 0;
}
