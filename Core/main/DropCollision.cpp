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
	GLboolean W, A, S, D, Q, E = false;
}

namespace Mouse {
	GLboolean appears = true;	
	GLdouble xInit, yInit;
	GLfloat xOffset, yOffset;
}

namespace Terrain {
	GLfloat rise = 8.0f;
	GLfloat waveInc = 0.0;
	GLfloat distance = -200.0f;
	GLfloat xDegree = 0.0f;
	GLfloat zDegree = 0.0f;
	unsigned int xyLength = 1000;
	unsigned int rowColCount = 42;
	float stride = (float)xyLength / (float)rowColCount;
}

namespace Player {
	GLboolean isGod = true;
	glm::vec3 camPos(0.0, 0.0, 0.0);
	glm::vec3 camLookPos(0.0, 0.0, -1.0);
	glm::mat4 persMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f);
	glm::mat4 viewMatrix(1);
	unsigned int location;
	std::array<float, 3> pos;
	MidPointQuad quad;
	float radius = 4.0f;
	float mvSpeed = 0.5f;
}

namespace Time {
	float threshold = 2.0f;
	float pace = 0.04f;
	std::chrono::steady_clock::time_point setupEnd;
	std::chrono::steady_clock::time_point frameBegin;
	std::chrono::duration<double> secSpan;
	std::chrono::duration<double, std::milli> milliSpan;
	std::chrono::duration<double, std::micro> microSpan;
	std::chrono::duration<double, std::nano> nanoSpan;
}

void God_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_P && action == GLFW_PRESS && Player::isGod) Player::isGod = false;
	else if(key == GLFW_KEY_P && action == GLFW_PRESS && !Player::isGod) Player::isGod = true;

	if(key == GLFW_KEY_W && action == GLFW_PRESS) Key::W = true;
	if(key == GLFW_KEY_W && action == GLFW_RELEASE) Key::W = false;
	if(Key::W && Player::isGod) Terrain::xDegree += 3.0f;
	if(Key::W && !Player::isGod) Player::location += (Terrain::rowColCount + 1) * 3;

	if(key == GLFW_KEY_A && action == GLFW_PRESS) Key::A = true;
	if(key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
	if(Key::A && Player::isGod) Terrain::zDegree += 3.0f;
	if(Key::A && !Player::isGod) Player::location -= 3;

	if(key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
	if(key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if(Key::S && Player::isGod) Terrain::xDegree -= 3.0f;
	if(Key::S && !Player::isGod) Player::location -= (Terrain::rowColCount + 1) * 3;

	if(key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
	if(key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
	if(Key::D && Player::isGod) Terrain::zDegree -= 3.0f;
	if(Key::D && !Player::isGod) Player::location += 3;

	if(key == GLFW_KEY_Q && action == GLFW_PRESS) Key::Q = true;
	if(key == GLFW_KEY_Q && action == GLFW_RELEASE) Key::Q = false;
	if(Key::Q && Player::isGod) Terrain::distance += 20.0f;

	if(key == GLFW_KEY_E && action == GLFW_PRESS) Key::E = true;
	if(key == GLFW_KEY_E && action == GLFW_RELEASE) Key::E = false;
	if(Key::E && Player::isGod) Terrain::distance -= 20.0f;
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
	glfwSetKeyCallback(window, God_keyCallback);
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
	GLSL_Waves Waves(parentDir + "//shaders//Waves.vert", parentDir + "//shaders//Waves.frag");

	GL4_BumpGrid bumpGrid(Terrain::rise, Terrain::xyLength, Terrain::rowColCount, Terrain::xyLength, Terrain::rowColCount);
	std::vector<float> mappedGrid;
	bumpGrid.map(&mappedGrid);

	GL4_Sphere playerSphere(Player::radius, 14, 14);
	// Player::location = mappedGrid.size() / 6 + Terrain::rowColCount * 3 / 2;
	// Player::location = mappedGrid.size() / 3 * 2 + Terrain::rowColCount * 6;
	Player::location = mappedGrid.size() / 2 - 1;
	Player::pos = { mappedGrid[Player::location], mappedGrid[Player::location + 1], mappedGrid[Player::location + 2] };

	Time::setupEnd = std::chrono::steady_clock::now();
	while(!glfwWindowShouldClose(window)){
		Time::frameBegin = std::chrono::steady_clock::now();
		Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::frameBegin - Time::setupEnd);

		Player::viewMatrix = glm::lookAt(Player::camPos, Player::camLookPos, glm::vec3(0.0, 1.0, 0.0));

		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glUseProgram(HeightRange.shaderProgID);
		glUseProgram(Waves.shaderProgID);
		Waves.set_waveHeight(Terrain::rise);

		if(Time::secSpan.count() > Time::threshold){
			Time::threshold = Time::secSpan.count() + Time::pace;
			Terrain::waveInc += 0.1;
			Waves.set_waveInc(Terrain::waveInc);
		}

		bumpGrid.relMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, Terrain::distance));
		bumpGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::xDegree), glm::vec3(1.0, 0.0, 0.0));
		bumpGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::zDegree), glm::vec3(0.0, 0.0, 1.0));
		Waves.set_mvpMatrix(Player::persMatrix * Player::viewMatrix * bumpGrid.relMatrix);
		Waves.set_renderMode(0);
		bumpGrid.draw();

		glUseProgram(Idle.shaderProgID);
		Player::pos = { mappedGrid[Player::location], mappedGrid[Player::location + 1], mappedGrid[Player::location + 2] };
		float newZ = std::abs(std::sin(Player::pos[2] + Terrain::waveInc)) * Terrain::rise + Player::radius * 0.6;
		playerSphere.relMatrix = glm::translate(bumpGrid.relMatrix, glm::vec3(Player::pos[0], Player::pos[1], newZ));
		// playerSphere.relMatrix *= glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
		Idle.set_mvpMatrix(Player::persMatrix * Player::viewMatrix * playerSphere.relMatrix);
		Idle.set_renderMode(1);
		playerSphere.draw(GL_TRIANGLES);

		glDisable(GL_DEPTH_TEST);
		glPointSize(6.0f);

		glfwSwapBuffers(window);
	}

    glfwTerminate();
    return 0;
}
