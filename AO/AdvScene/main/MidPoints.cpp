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

namespace Player {
	GLboolean isGod = true;
	glm::mat4 persMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f);
	glm::mat4 viewMatrix(1);
	glm::vec3 pos = glm::vec3(-4.0, -4.0, 0.0);
}

namespace Terrain {
	GLfloat rise = 30.0f;
	GLfloat distance = -200.0f;
	GLfloat xDegree = 0.0f;
	GLfloat zDegree = 0.0f;
}

namespace Time {
	std::chrono::steady_clock::time_point sceneSetup;
	std::chrono::steady_clock::time_point sceneUpdate;
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
	if(Key::W && !Player::isGod) Player::pos.y += 1.0f;

	if(key == GLFW_KEY_A && action == GLFW_PRESS) Key::A = true;
	if(key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
	if(Key::A && Player::isGod) Terrain::zDegree += 3.0f;
	if(Key::A && !Player::isGod) Player::pos.x -= 1.0f;

	if(key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
	if(key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if(Key::S && Player::isGod) Terrain::xDegree -= 3.0f;
	if(Key::S && !Player::isGod) Player::pos.y -= 1.0f;

	if(key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
	if(key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
	if(Key::D && Player::isGod) Terrain::zDegree -= 3.0f;
	if(Key::D && !Player::isGod) Player::pos.x += 1.0f;

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
	glViewport(0, 0, UI::height, UI::width);

	GLFWwindow* window = glfwCreateWindow(UI::width, UI::height, argv[0], nullptr, nullptr);
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
	GLSL_HeightRange HeightRange(parentDir + "//shaders//HeightRange.vert", parentDir + "//shaders//HeightRange.frag");

	GL4_BumpGrid FlatGrid(10.0, 100, 6, 100, 6);

	std::vector<MidPointQuad> midPointsQ;
	FlatGrid.gen_midPointQ(&midPointsQ);
	std::vector<MidPointTrig> midPointsT;
	FlatGrid.gen_midPointT(&midPointsT);
	GLuint testVAO[3];
	glGenVertexArrays(3, testVAO);
	glBindVertexArray(testVAO[0]);
	GLuint testVBO[3];
	glGenBuffers(3, testVBO);
	glBindBuffer(GL_ARRAY_BUFFER, testVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, midPointsQ.size() * sizeof(MidPointQuad), midPointsQ.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MidPointQuad), offsetof(MidPointQuad, pos));
	glEnableVertexAttribArray(0);
	glBindVertexArray(testVAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, testVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, midPointsT.size() * sizeof(MidPointTrig), midPointsT.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MidPointTrig), offsetof(MidPointTrig, pos));
	glEnableVertexAttribArray(0);
	Scene_PlaneCollision planeCollision;
	MidPointTrig proxMidPointT = planeCollision.proxMidPoint(&midPointsT, &glm::vec2(Player::pos.x, Player::pos.y));
	glBindVertexArray(testVAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, testVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3, &proxMidPointT.pos[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, offsetof(MidPointTrig, pos));
	glEnableVertexAttribArray(0);

	Time::sceneSetup = std::chrono::steady_clock::now();
	while(!glfwWindowShouldClose(window)){
		Time::sceneUpdate = std::chrono::steady_clock::now();
		Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::sceneUpdate - Time::sceneSetup);

		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 0.9f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPointSize(10.0f);
		glLineWidth(4.0f);
		// glUseProgram(HeightRange.shaderProgID);
		glUseProgram(Idle.shaderProgID);
		FlatGrid.relMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, Terrain::distance));
		FlatGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::xDegree), glm::vec3(1.0, 0.0, 0.0));
		FlatGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::zDegree), glm::vec3(0.0, 0.0, 1.0));
		Idle.set_mvpMatrix(Player::persMatrix * Player::viewMatrix * FlatGrid.relMatrix);
		Idle.set_renderMode(0);
		FlatGrid.draw();

		glDisable(GL_DEPTH_TEST);

		// Perform drawing without depth testing
		// Collision computation... Anton Says Hi

		glUseProgram(Idle.shaderProgID);
		Idle.set_mvpMatrix(Player::persMatrix * Player::viewMatrix * FlatGrid.relMatrix);
		Idle.set_renderMode(3);
		glBindVertexArray(testVAO[0]);
		glDrawArrays(GL_POINTS, 0, midPointsQ.size());
		Idle.set_renderMode(2);
		glBindVertexArray(testVAO[1]);
		glDrawArrays(GL_POINTS, 0, midPointsT.size());
		Idle.set_renderMode(1);
		glBindVertexArray(testVAO[2]);
		proxMidPointT = planeCollision.proxMidPoint(&midPointsT, &glm::vec2(Player::pos.x, Player::pos.y));
		glBindBuffer(GL_ARRAY_BUFFER, testVBO[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3, &proxMidPointT.pos[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, offsetof(MidPointTrig, pos));
		glDrawArrays(GL_POINTS, 0, 1);

		glfwSwapBuffers(window);
	}

    glfwTerminate();
    return 0;
}