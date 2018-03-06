#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>

#include "GL4_Api_Common.hpp"

#include "loaders/FileIO.hpp"
#include "graphics/GL4_LoadShaders.hpp"
#include "graphics/GL4_Vertex.hpp"
#include "graphics/factory/GL4_Vertex_Registry.hpp"
#include "graphics/entity/GL4_Mesh.hpp"
#include "graphics/GL4_Shader.hpp"
#include "graphics/GL4_Program.hpp"
#include "graphics/factory/GL4_Shader_Factory.hpp"
#include "scene/ErrorCode.hpp"

static char error_glfw3Init[] = "GLFW failed to initialize";
static char error_glfw3Window[] = "GLFW failed to create window";
static char error_glewInit[] = "GLEW failed to initialize";

namespace UI {
    int height = 1080;
    int width = 1320;
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

    if (glewInit() == GLEW_OK) std::cout << "GLEW initialized successfuly" << std::endl;
    else logError(__FILE__, __LINE__, error_glewInit);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat posData[] = {
        0.1, 0.6, 0.5,
        0.2, -0.4, 0.5,
        -0.1, -0.8, 0.5f
    };

    GLubyte colorData[] = {
        122, 122, 255, 255,
        100, 50, 200, 255,
        10, 10, 20, 255
    };


    std::string parentDir = getParentDirectory(argv[0]);

    GL4_Vertex_Registry vertexRegistry;
    vertexRegistry.create();
    GL4_Shader_Factory shaderFactory(parentDir);
    GL4_Program Idle = shaderFactory.get_program(_GL4_Program_ID::Idle);
    glUseProgram(Idle.get_progID());
    GL4_Mesh mesh1(3, {vertexRegistry.get_format(_GL4_Vertex_Feed_ID::pos_3f), vertexRegistry.get_format(_GL4_Vertex_Feed_ID::color_4f)});
    mesh1.set_feed_data(_GL4_Vertex_Feed_ID::pos_3f, &posData[0]);
    mesh1.set_feed_data(_GL4_Vertex_Feed_ID::color_4f, &colorData[0]);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(0.949f, 0.917f, 0.803f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPointSize(10.0f);

        mesh1.unordered_draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
