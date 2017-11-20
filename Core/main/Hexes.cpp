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

// #include "Geometry.h"
#include "Loaders.h"
#include "ManualSets.h"
#include "Pipeline.h"
#include "Scene.h"

const std::string getParentDirectory(const char* path) {
	const char* ptr = path + strlen(path);
	while (ptr != path && nullptr == strchr("\\/", *(--ptr)));
	std::size_t len = ptr - path;
	std::string result(path, len);
	std::cout << "Parent dir: " << result << std::endl;
	return result;
}

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
	GLboolean isGod = true;
	glm::mat4 perspectiveMatrix = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, -10.0f, 10.0f);
	glm::mat4 viewMatrix(1);
	glm::vec3 pos = glm::vec3(-4.0, -4.0, 0.0);
	float mvSpeed = 0.5f;
}

namespace Terrain {
	bool firstCreation = true;
	float pointSize = 3.0;
	float probability = 0.2;
	unsigned int xyCount = 200;
	float xRotation = 0.0;
	float zRotation = 0.0;
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
	
	float dot[6] = {0.0f, 0.0f, 0.0f, 3.0f, 3.0f, 0.0};
	GL4_DataSet dataSet(&dot[0], 6 * sizeof(float));

	float initPos[2] = {0.0, 0.0};
	/* Hexagon hexagon = createHex(5.0f, initPos);
	GL4_DataSet hexDataSet(&hexagon.sixProx[0], sizeof(float) * 18);
	initPos[1] = 20.0f;
	Hexagon hexagon2 = createHex(5.0f, initPos);
	GL4_DataSet hexDataSet2(&hexagon2.sixProx[0], sizeof(float) * 18);
	initPos[0] = 15.0f;
	initPos[1] = 10.0f; */
	HexagonIdx12 hexagon0 = createHexIdx12(12.0f, initPos, 0);
	GL4_DataSet hexDataSet0(&hexagon0.sixProx[0], sizeof(float) * 18);
	hexDataSet0.index(hexagon0.indices.data(), sizeof(GLuint) * 12);
	initPos[0] = 24.0f;
	initPos[1] = 24.0f;
	HexagonIdx12 hexagon1 = createHexIdx12(12.0f, initPos, 1);
	GL4_DataSet hexDataSet1(&hexagon1.sixProx[0], sizeof(float) * 18);
	hexDataSet1.index(hexagon1.indices.data(), sizeof(GLuint) * 12);
	initPos[0] = -24.0f;
	initPos[1] = -24.0f;
	HexagonIdx12 hexagon2 = createHexIdx12(12.0f, initPos, 3);
	GL4_DataSet hexDataSet2(&hexagon2.sixProx[0], sizeof(float) * 18);
	hexDataSet2.index(hexagon2.indices.data(), sizeof(GLuint) * 12);
	// GL4_HexGrid hexGrid(5.0f, 1, 2);

	Time::setupEnd = std::chrono::steady_clock::now();
	while(!glfwWindowShouldClose(window)){
		Time::frameBegin = std::chrono::steady_clock::now();
		Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::frameBegin - Time::setupEnd);

		glfwPollEvents();
		glClearColor(0.949f, 0.917f, 0.803f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glPointSize(6.0f);
		glLineWidth(4.0f);

		glUseProgram(Idle.shaderProgID);
		Idle.set_mvpMatrix(Player::perspectiveMatrix * Player::viewMatrix);
		Idle.set_renderMode(1);
		hexDataSet0.drawIdx(GL_LINES, 12);
		Idle.set_renderMode(2);
		hexDataSet1.drawIdx(GL_TRIANGLES, 12);
		Idle.set_renderMode(3);
		hexDataSet2.drawIdx(GL_TRIANGLES, 12);

		glfwSwapBuffers(window);
	}

    glfwTerminate();
    return 0;
}
