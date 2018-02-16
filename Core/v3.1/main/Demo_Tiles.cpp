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
#include "geometry/Tile.hpp"
#include "graphics/GL4_Shader.hpp"
#include "graphics/factory/GL4_Shader_Factory.hpp"
#include "graphics/GL4_Uniform.hpp"
#include "graphics/factory/GL4_Uniform_Factory.hpp"
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

    std::string parentDir = getParentDirectory(argv[0]);
    /* GLuint shaderProg = compileShaders(parentDir + "//shaders//Idle.vert", parentDir + "//shaders//Idle.frag");
    glUseProgram(shaderProg); */

    GL4_Vertex_Factory vertex_factory;
    GL4_Uniform_Factory uniform_factory;
    uniform_factory.create();
    GL4_Shader_Factory shader_factory(parentDir, &vertex_factory, &uniform_factory);
    shader_factory.create();
    GL4_Program Flatland = shader_factory.get_program(_GL4_Program_ID::Flatland);
    glUseProgram(Flatland.get_progID());
    GLuint data = 1;
    Flatland.set_data(_GL4_Uniform_Basic_ID::renderMode, &data);

    GL4_Mesh tile_mesh(4);
    Tile tile(0.5f, 0.5f);
    tile.create(&tile_mesh, &vertex_factory);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(0.949f, 0.917f, 0.803f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPointSize(10.0f);
        // mesh.mQuill.mode = GL_POINTS;
        // mesh.mQuill.unordered_draw();
        tile_mesh.mQuill.mode = GL_POINTS;
        tile_mesh.mQuill.unordered_draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
