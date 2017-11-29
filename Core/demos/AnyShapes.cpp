#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>
// #include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ManualSets.h"
#include "loaders/Loaders.h"
#include "pipeline/GLSL_Idle.hpp"
#include "geometry/GL4_DataSet.hpp"
#include "geometry/GL4_PolyFunc.hpp"
#include "geometry/PLY_CartesianGrid.hpp"

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

namespace Player {
	glm::mat4 perspectiveMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
	// glm::mat4 perspectiveMatrix = glm::ortho(-100.0f / 2, 100.0f / 2, -100.0f / 2, 100.0f / 2, -10.0f / 2, 10.0f / 2);
    glm::mat4 viewMatrix(1);
    glm::vec3 camPos(0.0, 0.0, 1.0f);
    glm::vec3 camLookPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

namespace Terrain {
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

namespace Math {
    float interval = 0.1f;
    unsigned int xNum = 1000;
	float yInit = 0.0f;
	float zInit = 0.0f;
}

void xFunc_Default(std::vector<float>* xVals){
    xVals->resize(Math::xNum);
    float offsetX = Math::interval / 2.0f;
    short int indexOffset = -1;
    unsigned int repCount = Math::xNum;
    if(repCount % 2 == 1){
        xVals->at(repCount / 2) = 0.0f;
        offsetX = 0.0f;
        indexOffset = 0;
        repCount--;
    }
    for(unsigned int xElem = repCount / 2; xElem > 0; xElem--){
        xVals->at(repCount / 2 - xElem) = -1.0f * Math::interval * xElem + offsetX;
        xVals->at(repCount / 2 + (xElem + indexOffset)) = Math::interval * xElem - offsetX;
	}
	
	std::sort(xVals->begin(), xVals->end());
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
	Time::setupBegin = std::chrono::steady_clock::now();

	if (glfwInit() == GLFW_TRUE)  std::cout << "GLFW initialized successfuly" << std::endl;
	else {
		std::cerr << "GLFW failed to initialize" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glViewport(0, 0, UI::width, UI::height);

	GLFWwindow* window = glfwCreateWindow(UI::width,  UI::height, argv[0], nullptr, nullptr);
	if (nullptr != window) std::cout << "GLFW window created successfuly" << std::endl;
	else {
		std::cerr << "GLFW failed to create window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &UI::width, &UI::height);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);

	if (glewInit() == GLEW_OK) std::cout << "GLEW initialized successfuly" << std::endl;
	else {
		std::cerr << "GLEW failed to initialize" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::string parentDir = getParentDirectory(argv[0]);
	GLSL_Idle Idle(parentDir + "//shaders//Idle.vert", parentDir + "//shaders//Idle.frag");

    Player::viewMatrix = glm::lookAt(Player::camPos, Player::camLookPos, glm::vec3(0.0, 1.0, 0.0));

    GL4_PolyFunc polyFunc;
    PLY_CartesianGrid cartesianGrid(&polyFunc, 10.0f, 10, 10.0f, 20);

    Time::setupEnd = std::chrono::steady_clock::now();
    while(!glfwWindowShouldClose(window)){
        Time::frameBegin = std::chrono::steady_clock::now();
        Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::frameBegin - Time::setupEnd);

        glfwPollEvents();
        glClearColor(0.949f, 0.917f, 0.803f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glPointSize(8.0f);
        glLineWidth(8.0f);

        glUseProgram(Idle.shaderProgID);
        Idle.set_renderMode(0);
        Idle.set_mvpMatrix(Player::viewMatrix * Player::perspectiveMatrix);
        polyFunc.draw(GL_TRIANGLES);

		glfwSwapBuffers(window);
	}

    glfwTerminate();
    return 0;
}
