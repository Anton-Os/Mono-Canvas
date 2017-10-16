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

#include "Geometry.h"
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
	glm::vec3 pos = glm::vec3(-11.0, -11.0, 0.0);
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

int main(int argc, char** argv){
    /* -- -- -- Creation of OpenGL Context, Windowing, and Handling User Input -- -- -- */
    if(glfwInit() == GLFW_TRUE)  std::cout << "GLFW initialized successfuly" << std::endl;
    else {
        std::cerr << "GLFW failed to initialize" << std::endl;
        return -1;
    }

    int windowHeight = 900;
    int windowWidth = 1100;

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 
    glViewport(0, 0, windowHeight, windowWidth);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Asset Import", nullptr, nullptr);
    if(nullptr != window) std::cout << "GLFW window created successfuly" << std::endl;
    else {
        std::cerr << "GLFW failed to create window" << std::endl;
        return -1;
    }

	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
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

	GLuint testVAO;
	glGenVertexArrays(1, &testVAO);

	std::string Idle_vert = parentDir + "//shaders//Idle.vert";
	std::string Idle_frag = parentDir + "//shaders//Idle.frag";
	GLuint Idle_uiID = compileShaders(Idle_vert, Idle_frag);
	glUseProgram(Idle_uiID);
	GLSL_Idle Idle(Idle_uiID);
	Idle.initUniforms();

	std::string HeightRange_vert = parentDir + "//shaders//HeightRange.vert";
	std::string HeightRange_frag = parentDir + "//shaders//HeightRange.frag";
	GLuint HeightRange_uiID = compileShaders(HeightRange_vert, HeightRange_frag);
	glUseProgram(HeightRange_uiID);
	GLSL_HeightRange HeightRange(HeightRange_uiID);
	HeightRange.initUniforms();

	GL4_BumpGrid FlatGrid(3.0, 100, 4, 100, 4);

	std::vector<MidPoint> midPoints;
	FlatGrid.get_midPoint(&midPoints);
	std::vector<GLfloat> collisionPos;
	FlatGrid.map(&collisionPos);
	std::array<float, 12> fourProxPos;
	std::array<float, 4> fourProxDist;
	
	GLuint tileLit;
	glGenVertexArrays(1, &tileLit);
	std::array<unsigned int, 6> squareIndices = { 0, 1, 2, 3, 1, 2};
	loadIndices(tileLit, 6, GL_STATIC_DRAW, squareIndices.data());
	
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
		glUseProgram(HeightRange_uiID);

		FlatGrid.relMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, Terrain::distance));
		FlatGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::xDegree), glm::vec3(1.0, 0.0, 0.0));
		FlatGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::zDegree), glm::vec3(0.0, 0.0, 1.0));
		HeightRange.set_mvpMatrix(Player::persMatrix * Player::viewMatrix * FlatGrid.relMatrix);
		HeightRange.set_rise(3.0 * 2);
		HeightRange.set_renderMode(1);
		// FlatGrid.drawFixed(GL_TRIANGLES, Time::secSpan.count() * 3 * 40);
		FlatGrid.draw();

		glDisable(GL_DEPTH_TEST);

		// Perform drawing without depth testing
		// Collision computation... Anton Says Hi

		compFourProx(&fourProxPos, &fourProxDist, &glm::vec2(Player::pos.x, Player::pos.y), &collisionPos);
		Player::pos.z = compLocalZ(&fourProxPos, &fourProxDist);
		loadData(tileLit, 12, GL_STATIC_DRAW, fourProxPos.data(), nullptr, nullptr, nullptr);

		glUseProgram(Idle_uiID);
		glBindVertexArray(tileLit);
		Idle.set_mvpMatrix(Player::persMatrix * Player::viewMatrix * FlatGrid.relMatrix);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resourcdes -- -- -- */

    glfwTerminate();
    return 0;
}
