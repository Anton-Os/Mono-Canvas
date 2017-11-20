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
	GLfloat rise = 16.0f;
	GLfloat waveInc = 0.0;
	GLfloat distance = -200.0f;
	GLfloat xDegree = 0.0f;
	GLfloat zDegree = 0.0f;
	unsigned int rowColCount = 42;
}

namespace Player {
	GLboolean isGod = true;
	glm::mat4 persMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f);
	glm::mat4 viewMatrix(1);
	unsigned int pos;
	MidPointQuad quad;
	float radius = 3.0f;
	float mvSpeed = 0.5f;
}

namespace Time {
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
	if(Key::W && !Player::isGod) Player::pos += Terrain::rowColCount;

	if(key == GLFW_KEY_A && action == GLFW_PRESS) Key::A = true;
	if(key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
	if(Key::A && Player::isGod) Terrain::zDegree += 3.0f;
	if(Key::A && !Player::isGod) Player::pos--;

	if(key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
	if(key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if(Key::S && Player::isGod) Terrain::xDegree -= 3.0f;
	if(Key::S && !Player::isGod) Player::pos -= Terrain::rowColCount;

	if(key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
	if(key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
	if(Key::D && Player::isGod) Terrain::zDegree -= 3.0f;
	if(Key::D && !Player::isGod) Player::pos++;

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

	GL4_BumpGrid bumpGrid(Terrain::rise, 500, Terrain::rowColCount, 500, Terrain::rowColCount);
	std::vector<MidPointQuad> midPointsQ;
	bumpGrid.gen_midPointQ(&midPointsQ);
	GL4_DataSet bumpGrid_midPointsQ(midPointsQ.data(), midPointsQ.size() * sizeof(MidPointQuad), sizeof(MidPointQuad), offsetof(MidPointQuad, pos));
	GL4_Sphere playerSphere(Player::radius, 14, 14);
	Player::pos = midPointsQ.size() / 2 + Terrain::rowColCount / 2;
	Player::quad = midPointsQ[Player::pos];
	// playerSphere.relMatrix = glm::translate(glm::mat4(1), glm::vec3(Player::quad.pos[0], Player::quad.pos[1], Player::quad.pos[2] + Player::radius));

	Scene_PlaneCollision planeCollsion;
	std::vector<float> clampedVals;
	planeCollsion.waves(Terrain::rise, &midPointsQ, &clampedVals);

	Time::setupEnd = std::chrono::steady_clock::now();
	while(!glfwWindowShouldClose(window)){
		Time::frameBegin = std::chrono::steady_clock::now();
		Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::frameBegin - Time::setupEnd);

		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glUseProgram(HeightRange.shaderProgID);
		glUseProgram(Waves.shaderProgID);
		Waves.set_waveHeight(Terrain::rise / 2.0);
		Waves.set_waveInc(Terrain::waveInc);

		bumpGrid.relMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, Terrain::distance));
		bumpGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::xDegree), glm::vec3(1.0, 0.0, 0.0));
		bumpGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::zDegree), glm::vec3(0.0, 0.0, 1.0));
		Waves.set_mvpMatrix(Player::persMatrix * Player::viewMatrix * bumpGrid.relMatrix);
		Waves.set_renderMode(0);
		bumpGrid.draw();
		Player::quad = midPointsQ[Player::pos];
		playerSphere.relMatrix = glm::translate(bumpGrid.relMatrix, glm::vec3(Player::quad.pos[0], Player::quad.pos[1], Player::quad.pos[2] + Player::radius));
		// playerSphere.relMatrix = glm::translate(glm::mat4(1), glm::vec3(Player::quad.pos[0], Player::quad.pos[1], Player::quad.pos[2] + Player::radius));		
		Waves.set_mvpMatrix(Player::persMatrix * Player::viewMatrix * playerSphere.relMatrix);
		Waves.set_renderMode(2);
		playerSphere.draw(GL_TRIANGLES);

		glDisable(GL_DEPTH_TEST);
		glPointSize(6.0f);

		Waves.set_mvpMatrix(Player::persMatrix * Player::viewMatrix * bumpGrid.relMatrix);
		Waves.set_renderMode(1);
		bumpGrid_midPointsQ.draw(GL_POINTS, midPointsQ.size());

		glDisable(GL_DEPTH_TEST);

		// Perform drawing without depth testing
		// Collision computation... Anton Says Hi

		glfwSwapBuffers(window);
	}

    glfwTerminate();
    return 0;
}
