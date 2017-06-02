
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Common.h>

/* Handles main OpenGL functionality */

GLfloat scaleX = 0.4f;
GLfloat scaleY = 0.4f;
GLfloat moveX = 0;
GLfloat moveY = 0;
GLfloat timeAngle = 4.0f;
GLfloat rotateX = 0;
GLfloat rotateY = 0;
GLfloat rotateZ = -1.0f;

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

    GLuint VBO, VAO, EBO;
    GLuint VBOs[100];
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(100, VBOs);
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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxishIndices), boxishIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinding
    glBindVertexArray(0); // Unbinding

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 0.88, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 9);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
