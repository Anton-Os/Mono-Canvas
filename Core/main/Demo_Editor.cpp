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

#include "Loaders.h"
#include "pipeline/GLSL_Idle.hpp"
#include "pipeline/GLSL_ColorMe.hpp"
#include "geometry/polybase/GL4_PolyFunc.hpp"
#include "geometry/polyform/Polyform_Box.hpp"
#include "geometry/polyform/Polyform_Rubiks.hpp"
#include "scene/Editor.hpp"

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
	bool isGod = true;
	// glm::mat4 projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -20.0f, 20.0f);
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f);
    glm::mat4 viewMatrix(1);
    glm::vec3 camPos(0.0, 0.0, 1.0f);
    glm::vec3 camLookPos = glm::vec3(0.0f, 0.0f, 0.0f);
	std::array<int, 3> location = {0, 0, 0};
	float rtFactor = 5.0f;
	float mvSpeed = 0.3f;
}

namespace Terrain {
	bool spawnVertex = false;
	float xAngle = 0.0f;
	float yAngle = 0.0f;
	float zAngle = 0.0f;
	float distance = -2.0f;
	/* float minimum = -12.7f / 7;
	float maximum = 12.7f / 7; */
	float minimum = -1.0f;
	float maximum = 1.0f;
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

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	// State Switching

	if(key == GLFW_KEY_1 && action == GLFW_PRESS){
		if(Player::isGod) Player::isGod = false;
		else if(!Player::isGod) Player::isGod = true;
	}

	if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		Terrain::spawnVertex = true;
	}

	// Continuous actions
	
	if(key == GLFW_KEY_A && action == GLFW_PRESS) Key::A = true;
	if(key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
	if(Player::isGod && Key::A) Terrain::yAngle += Player::rtFactor;
	else if(!Player::isGod && Key::A) Player::location[0]--;

	if(key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
	if(key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
	if(Player::isGod && Key::D) Terrain::yAngle -= Player::rtFactor;
	else if(!Player::isGod && Key::D) Player::location[0]++;

	if(key == GLFW_KEY_W && action == GLFW_PRESS) Key::W = true;
	if(key == GLFW_KEY_W && action == GLFW_RELEASE) Key::W = false;
	if(Player::isGod && Key::W) Terrain::xAngle += Player::rtFactor;
	else if(!Player::isGod && Key::W) Player::location[1]++;

	if(key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
	if(key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if(Player::isGod && Key::S) Terrain::xAngle -= Player::rtFactor;
	else if(!Player::isGod && Key::S) Player::location[1]--;

	if(key == GLFW_KEY_Q && action == GLFW_PRESS) Key::Q = true;
	if(key == GLFW_KEY_Q && action == GLFW_RELEASE) Key::Q = false;
	if(Player::isGod && Key::Q) Terrain::distance += Player::mvSpeed;
	else if(!Player::isGod && Key::Q) Player::location[2]--;

	if(key == GLFW_KEY_E && action == GLFW_PRESS) Key::E = true;
	if(key == GLFW_KEY_E && action == GLFW_RELEASE) Key::E = false;
	if(Player::isGod && Key::E) Terrain::distance -= Player::mvSpeed;
	else if(!Player::isGod && Key::E) Player::location[2]++;
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

	GL4_PolyFunc polyFunc;
	Polyform_Box polyBox(0.2f, 0.2f, 0.2f);
	Polyform_Rubiks polyRubiks(10, 10, 10);

	Editor editor(&polyFunc, &polyBox, &polyRubiks);

    Player::viewMatrix = glm::lookAt(Player::camPos, Player::camLookPos, glm::vec3(0.0, 1.0, 0.0));

    Time::setupEnd = std::chrono::steady_clock::now();
    while(!glfwWindowShouldClose(window)){
        Time::frameBegin = std::chrono::steady_clock::now();
        Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::frameBegin - Time::setupEnd);

        glfwPollEvents();
        // glClearColor(0.949f, 0.917f, 0.803f, 1.0f);
        glClearColor(0.0, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glPointSize(3.0f);
        glLineWidth(8.0f);

		Player::viewMatrix = glm::lookAt(Player::camPos, Player::camLookPos, glm::vec3(0.0, 1.0, 0.0));

		polyFunc.relMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, Terrain::distance));
        polyFunc.relMatrix = glm::rotate(polyFunc.relMatrix, glm::radians<float>(Terrain::xAngle), glm::vec3(1.0, 0.0, 0.0));
		polyFunc.relMatrix = glm::rotate(polyFunc.relMatrix, glm::radians<float>(Terrain::yAngle), glm::vec3(0.0, 1.0, 0.0));

		glUseProgram(Idle.shaderProgID);
		Idle.set_renderMode(2);
		Idle.set_mvpMatrix(Player::projectionMatrix * Player::viewMatrix * polyFunc.relMatrix);
		
		editor.setCursor(&Player::location);
		polyFunc.drawXI(GL_POINTS);

		glPointSize(10.0f);
		Idle.set_renderMode(1);

		editor.cursor3D.drawXI(GL_POINTS);
		if(Terrain::spawnVertex){
			editor.spawnVertex(Player::location[0], Player::location[1], Player::location[2]);
			// editor.model.drawXI(GL_TRIANGLES);
			Terrain::spawnVertex = false;
		}
		Idle.set_renderMode(0);
		editor.model.drawXI(GL_TRIANGLE_FAN);

		glfwSwapBuffers(window);
	}

    glfwTerminate();
    return 0;
}
