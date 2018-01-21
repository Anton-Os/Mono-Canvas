#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "loaders/FileIO.hpp"
#include "loaders/LoadShaders.hpp"
#include "geometry/GL4_Vertex.hpp"
#include "geometry/GL4_Vertex_Factory.hpp"
#include "geometry/GL4_Mesh.hpp"
#include "geometry/polybase/GL4_PolyFunc.hpp"
#include "geometry/polyform/Grid.hpp"
#include "scene/ErrorCode.hpp"

static char error_glfw3Init[] = "GLFW failed to initialize";
static char error_glfw3Window[] = "GLFW failed to create window";
static char error_glewInit[] = "GLEW failed to initialize";

namespace UI {
    int height = 1080;
    int width = 1320;
}

namespace Key {
    bool W, A, S, D, Q, E = false;
}

namespace Mouse {
    GLboolean appears = true;
    GLdouble xInit, yInit;
    GLfloat xOffset, yOffset;
}

namespace Time {
    std::chrono::steady_clock::time_point setupBegin;
    std::chrono::steady_clock::time_point setupEnd;
    std::chrono::steady_clock::time_point frameBegin;
    std::chrono::duration<double> secSpan;
    std::chrono::duration<double, std::milli> milliSpan;
    std::chrono::duration<double, std::micro> microSpan;
    std::chrono::duration<double, std::nano> nanoSpan;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // State Switching

    if(key == GLFW_KEY_1 && action == GLFW_PRESS) std::cout << "Key 1 Pressed" << std::endl;
    if(key == GLFW_KEY_2 && action == GLFW_PRESS) std::cout << "Key 2 Pressed" << std::endl;
    if(key == GLFW_KEY_3 && action == GLFW_PRESS) std::cout << "Key 3 Pressed" << std::endl;

    // Continuous actions

    if(key == GLFW_KEY_A && action == GLFW_PRESS) Key::A = true;
    if(key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
    if(Key::A) std::cout << "Key A Held..." << std::endl;

    if(key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
    if(key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
    if(Key::D) std::cout << "Key D Held..." << std::endl;

    if(key == GLFW_KEY_W && action == GLFW_PRESS) Key::W = true;
    if(key == GLFW_KEY_W && action == GLFW_RELEASE) Key::W = false;
    if(Key::W) std::cout << "Key W Held..." << std::endl;

    if(key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
    if(key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
    if(Key::S) std::cout << "Key S Held..." << std::endl;
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos){
    if(Mouse::appears) Mouse::appears = false;
    else {
        if(xpos != Mouse::xInit) Mouse::xOffset -= GLfloat((xpos - Mouse::xInit));
        if(ypos != Mouse::yInit) Mouse::yOffset -= GLfloat((ypos - Mouse::yInit));
    }

    Mouse::xInit = xpos;
    Mouse::yInit = ypos;
}


int main(int argc, char** argv) {
    if (glfwInit() == GLFW_TRUE)  std::cout << "GLFW initialized successfuly" << std::endl;
    else logError(__FILE__, __LINE__, error_glfw3Init);

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glViewport(0, 0, UI::width, UI::height);

    GLFWwindow* window = glfwCreateWindow(UI::width,  UI::height, argv[0], nullptr, nullptr);
    if (nullptr != window) std::cout << "GLFW window created successfuly" << std::endl;
    else logError(__FILE__, __LINE__, error_glfw3Window);


    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &UI::width, &UI::height);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    if (glewInit() == GLEW_OK) std::cout << "GLEW initialized successfuly" << std::endl;
    else logError(__FILE__, __LINE__, error_glewInit);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::string parentDir = getParentDirectory(argv[0]);
    GLuint shaderProg = compileShaders(parentDir + "//shaders//Idle.vert", parentDir + "//shaders//Idle.frag");
    glUseProgram(shaderProg);

    GL4_PolyFunc polyFunc;
    Polyform_Grid polyGrid(&polyFunc, 1.0f, 5, 1.0f, 5);
    GL4_Vertex_Factory vertex_factory;
    GL4_Mesh mesh(polyFunc.get_xCount() * polyFunc.get_yCount() * polyFunc.get_zCount());
    polyFunc.create(&mesh, &vertex_factory);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(0.949f, 0.917f, 0.803f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPointSize(10.0f);
        mesh.quill.mode = GL_POINTS;
        mesh.quill.unordered_draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
