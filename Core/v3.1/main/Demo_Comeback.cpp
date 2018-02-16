#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>

#include "GL4_Api_Common.hpp"

#include "loaders/FileIO.hpp"
#include "graphics/GL4_LoadShaders.hpp"
#include "graphics/GL4_Vertex.hpp"
#include "graphics/factory/GL4_Vertex_Factory.hpp"
#include "graphics/entity/GL4_Mesh.hpp"
#include "geometry/polybase/GL4_PolyFunc.hpp"
#include "geometry/polyform/GL4_PolyGrid.hpp"
#include "scene/KeyManager.hpp"
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

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos){
    if(Mouse::appears) Mouse::appears = false;
    else {
        if(xpos != Mouse::xInit) Mouse::xOffset -= GLfloat((xpos - Mouse::xInit));
        if(ypos != Mouse::yInit) Mouse::yOffset -= GLfloat((ypos - Mouse::yInit));
    }

    Mouse::xInit = xpos;
    Mouse::yInit = ypos;
}

void keySwitch_callback(int* s){
    std::cout << "Owch " << *s << " state" << std::endl;
}

void keyButton_callback(bool* b){
    std::cout << "Held: " << *b << " amount" << std::endl;
}

void keyCounter_callback(int* n){
    std::cout << "Number is now " << *n << std::endl;
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

    Key_Switch keySwitch;
    keySwitch.states.resize(3);
    keySwitch.states[0] = 0;
    keySwitch.states[1] = 1;
    keySwitch.states[2] = -1;
    keySwitch.key = GLFW_KEY_H;
    keySwitch.callback = keySwitch_callback;

    Key_Button keyButton;
    keyButton.key = GLFW_KEY_P;
    keyButton.callback = keyButton_callback;

    Key_Counter keyCounter;
    keyCounter.incKey = GLFW_KEY_Z;
    keyCounter.decKey = GLFW_KEY_C;
    keyCounter.callback = keyCounter_callback;

    KeyManager keyManager;
    keyManager.add_switch(&keySwitch);
    keyManager.add_button(&keyButton);
    keyManager.add_counter(&keyCounter);
    keyManager.set_current(window);

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
        mesh.mQuill.mode = GL_POINTS;
        mesh.mQuill.ordered_draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
