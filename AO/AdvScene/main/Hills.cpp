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
#include "PipelineCtrl.h"
#include "Loaders.h"
#include "CompositeGeo.h"

const std::string getParentDirectory(const char* path) {
	const char* ptr = path + strlen(path);
	while (ptr != path && nullptr == strchr("\\/", *(--ptr)));
	std::size_t len = ptr - path;
	std::string result(path, len);
	std::cout << "Parent dir: " << result << std::endl;
	return result;
}

namespace Key {
	GLboolean P, W, A, S, D = false;
}

namespace Mouse {
	GLboolean appears = true;	
	GLdouble xInit, yInit;
	GLfloat xOffset, yOffset;
}

namespace Player {
	GLboolean isGod = true;
	glm::mat4 viewMatrix(1);
}

namespace Terrain {
	GLfloat rise = 30.0f;
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
	GLuint frameCount = 1;
}

void God_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_P && action == GLFW_PRESS) Key::P = true;
	if(key == GLFW_KEY_P && action == GLFW_RELEASE) Key::P = false;
	if(Key::P) Player::isGod = false;

	if(key == GLFW_KEY_W && action == GLFW_PRESS) Key::W = true;
	if(key == GLFW_KEY_W && action == GLFW_RELEASE) Key::W = false;
	if(Key::W) Terrain::xDegree += 3.0f;

	if(key == GLFW_KEY_A && action == GLFW_PRESS) Key::A = true;
	if(key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
	if(Key::A) Terrain::zDegree += 3.0f;

	if(key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
	if(key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if(Key::S) Terrain::xDegree -= 3.0f;

	if(key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
	if(key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
	if(Key::D) Terrain::zDegree -= 3.0f;
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

	loadData(testVAO, sizeof(squarePos) / sizeof(GLfloat), GL_STATIC_DRAW, &squarePos[0], nullptr, nullptr, nullptr);
	loadIndices(testVAO, sizeof(squareIndices) / sizeof(GLuint), GL_STATIC_DRAW, &squareIndices[0]);

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

	GL4_BumpGrid BumpGrid(Terrain::rise, 100, 20, 100, 20);
	GL4_BumpGrid FlatGrid(3.0, 100, 20, 100, 20);

	glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f);
	
	Time::sceneSetup = std::chrono::steady_clock::now();
	while(!glfwWindowShouldClose(window)){
		Time::sceneUpdate = std::chrono::steady_clock::now();
		Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::sceneUpdate - Time::sceneSetup);

		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPointSize(10.0f);
		glLineWidth(4.0f);
		glUseProgram(HeightRange_uiID);
		BumpGrid.relMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, -200.0f));
		BumpGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::xDegree), glm::vec3(1.0, 0.0, 0.0));
		BumpGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::zDegree), glm::vec3(0.0, 0.0, 1.0));
		HeightRange.set_mvpMatrix(perspectiveMatrix * Player::viewMatrix * BumpGrid.relMatrix);
		HeightRange.set_rise(Terrain::rise);
		HeightRange.set_renderMode(4);
		/* glUseProgram(Idle_uiID);
		Idle.set_mvpMatrix(perspectiveMatrix * Player::viewMatrix * BumpGrid.relMatrix); */
		// BumpGrid.draw();
		// BumpGrid.drawFixed(GL_POINTS, Time::secSpan.count());
		// BumpGrid.drawFixed(GL_LINES, Time::secSpan.count() * 2);
		BumpGrid.drawFixed(GL_TRIANGLES, Time::secSpan.count() * 3 * 40);

		FlatGrid.relMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, -185.0f));
		FlatGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::xDegree), glm::vec3(1.0, 0.0, 0.0));
		FlatGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(Terrain::zDegree), glm::vec3(0.0, 0.0, 1.0));
		HeightRange.set_mvpMatrix(perspectiveMatrix * Player::viewMatrix * FlatGrid.relMatrix);
		HeightRange.set_rise(3.0 * 2);
		HeightRange.set_renderMode(3);
		FlatGrid.drawFixed(GL_TRIANGLES, Time::secSpan.count() * 3 * 40);

		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resourcdes -- -- -- */

    glfwTerminate();
    return 0;
}