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
#include "pipeline/GLSL_Tilemap.hpp"
#include "geometry/polybase/GL4_PolyFunc.hpp"
#include "geometry/polyform/Polyform_Grid.hpp"
#include "geometry/polyform/Polyform_Tilemap.hpp"

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
	// glm::mat4 projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -20.0f, 20.0f);
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f);
    glm::mat4 viewMatrix(1);
    glm::vec3 camPos(0.0, 0.0, 1.0f);
    glm::vec3 camLookPos = glm::vec3(0.0f, 0.0f, 0.0f);
	float rtFactor = 5.0f;
	float mvSpeed = 0.1f;
}

namespace Terrain {
	float xAngle = 0.0f;
	float yAngle = 0.0f;
	float zAngle = 0.0f;
	float distance = -4.0f;
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
	if(Key::A) Terrain::yAngle += Player::rtFactor;

	if(key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
	if(key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
	if(Key::D) Terrain::yAngle -= Player::rtFactor;

	if(key == GLFW_KEY_W && action == GLFW_PRESS) Key::W = true;
	if(key == GLFW_KEY_W && action == GLFW_RELEASE) Key::W = false;
	if(Key::W) Terrain::xAngle += Player::rtFactor;

	if(key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
	if(key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if(Key::S) Terrain::xAngle -= Player::rtFactor;

	if(key == GLFW_KEY_Q && action == GLFW_PRESS) Key::Q = true;
	if(key == GLFW_KEY_Q && action == GLFW_RELEASE) Key::Q = false;
	if(Key::Q) Terrain::distance += Player::mvSpeed;

	if(key == GLFW_KEY_E && action == GLFW_PRESS) Key::E = true;
	if(key == GLFW_KEY_E && action == GLFW_RELEASE) Key::E = false;
	if(Key::E) Terrain::distance -= Player::mvSpeed;
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
	GLSL_Tilemap Tilemap(parentDir + "//shaders//Tilemap.vert", parentDir + "//shaders//Tilemap.frag");

	std::string sandTexPath = parentDir + "//res//LightWood.ktx";
	GLuint sandTex = createTexture(sandTexPath.c_str());
	glBindTextureUnit(0, sandTex);

    Player::viewMatrix = glm::lookAt(Player::camPos, Player::camLookPos, glm::vec3(0.0, 1.0, 0.0));

	Polyform_Grid grid(0.5f, 10, 0.5f, 10);
	GL4_PolyClone polyClone;
	Polyform_Tilemap tilemap(&polyClone, &grid);
	Polyform_Tilemap_Picker tilemapPicker;
	tilemapPicker.weights.push_back(0.6f);
	tilemapPicker.states.push_back(1);
	tilemapPicker.weights.push_back(0.3f);
	tilemapPicker.states.push_back(2);
	tilemapPicker.weights.push_back(0.2f);
	tilemapPicker.states.push_back(3);
	// tilemap.gen_points(0.5f);
	tilemap.gen_points(&tilemapPicker);
	GL4_Tree_Meta treeMeta;
	polyClone.exportMeta(&treeMeta);

    Time::setupEnd = std::chrono::steady_clock::now();
    while(!glfwWindowShouldClose(window)){
        Time::frameBegin = std::chrono::steady_clock::now();
        Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::frameBegin - Time::setupEnd);

        glfwPollEvents();
        glClearColor(0.949f, 0.917f, 0.803f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

		glUseProgram(Tilemap.shaderProgID);
		Tilemap.set_mvpMatrix(Player::projectionMatrix * Player::viewMatrix);
		
		for(unsigned m = 0; m < treeMeta.nodeCount; m++){
			Tilemap.set_mvpMatrix(Player::projectionMatrix * Player::viewMatrix * polyClone.get_mtx(m));
			Tilemap.set_state(tilemap.get_state(m));
			polyClone.draw(m, GL_TRIANGLES);
		}

        glPointSize(8.0f);
        glLineWidth(8.0f);

		glfwSwapBuffers(window);
	}

    glfwTerminate();
    return 0;
}
