#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
// #include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ManualSets.h"
#include "loaders/Loaders.h"
#include "pipeline/GLSL_Idle.hpp"
#include "pipeline/GLSL_StateStream.hpp"
#include "geometry/GL4_DataSet.hpp"
#include "geometry/GL4_Grid.hpp"
#include "geometry/GL4_BumpGrid.hpp"
#include "scene/CellSim.hpp"

namespace UI {
	int height = 1080;
	int width = 1320;
}

namespace Key {
	GLboolean W, A, S, D, Q, E = false;
}

namespace Mouse {
	GLboolean appears = true;	
	GLdouble xInit, yInit;
	GLfloat xOffset, yOffset;
}

namespace Player {
	GLboolean isGod = true;
	glm::mat4 perspectiveMatrix = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, -10.0f, 10.0f);
	glm::mat4 viewMatrix(1);
	glm::vec3 pos = glm::vec3(-4.0, -4.0, 0.0);
	float mvSpeed = 0.5f;
}

namespace Terrain {
	bool firstCreation = true;
	float pointSize = 3.0;
	// 	float probability = 0.02;
	float probability = 0.2;
	unsigned int xyCount = 200;
	float xRotation = 0.0;
	float zRotation = 0.0;
}

namespace Time {
	float threshold = 2.0;
	float pace = 0.05f;
	std::chrono::steady_clock::time_point sceneSetup;
	std::chrono::steady_clock::time_point sceneUpdate;
	std::chrono::duration<double> secSpan;
	std::chrono::duration<double, std::milli> milliSpan;
	std::chrono::duration<double, std::micro> microSpan;
	std::chrono::duration<double, std::nano> nanoSpan;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_A && action == GLFW_PRESS) Key::A = true;
	if(key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
	if(Key::A) Terrain::xRotation += 4.0;

	if(key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
	if(key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
	if(Key::D) Terrain::xRotation -= 4.0;

	if(key == GLFW_KEY_W && action == GLFW_PRESS) Key::W = true;
	if(key == GLFW_KEY_W && action == GLFW_RELEASE) Key::W = false;
	if(Key::W) Terrain::zRotation += 4.0;

	if(key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
	if(key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if(Key::S) Terrain::zRotation -= 4.0;
}

int main(int argc, char** argv) {

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
	// glfwSetCursorPosCallback(window, cursorPosCallback);

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
	GLSL_StateStream stateStream(parentDir + "//shaders//StateStream.vert", parentDir + "//shaders//StateStream.frag");

	GL4_Grid bumpGrid(194, Terrain::xyCount, 194, Terrain::xyCount);

	Scene_CellSim cellSim(&bumpGrid, Terrain::probability);
	// cellSim.gen_proxPoints();
	cellSim.updateStates();

	Time::sceneSetup = std::chrono::steady_clock::now();
	while(!glfwWindowShouldClose(window)){
		Time::sceneUpdate = std::chrono::steady_clock::now();
		Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::sceneUpdate - Time::sceneSetup);

		glfwPollEvents();
		// glClearColor(0.949f, 0.917f, 0.803f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPointSize(Terrain::pointSize);
		glUseProgram(stateStream.shaderProgID);

		if(Time::secSpan.count() > Time::threshold){
			Time::threshold = Time::secSpan.count() + Time::pace;
			cellSim.scanGrid();
			cellSim.updateStates();
		}
		bumpGrid.relMatrix = glm::rotate(glm::mat4(1), glm::radians(Terrain::xRotation), glm::vec3(0.0, 1.0, 0.0));
		bumpGrid.relMatrix = glm::rotate(bumpGrid.relMatrix, glm::radians(Terrain::zRotation), glm::vec3(0.0, 0.0, 1.0));
		stateStream.set_mvpMatrix(Player::perspectiveMatrix * Player::viewMatrix * bumpGrid.relMatrix);
		bumpGrid.drawXI(GL_POINTS);

		glDisable(GL_DEPTH_TEST);

		glfwSwapBuffers(window);
	}

    glfwTerminate();
    return 0;
}
