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
	// glm::mat4 persMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
	glm::mat4 persMatrix = glm::ortho(-1 * ((float)UI::width / 108), ((float)UI::width / 108), -1 * ((float)UI::height / 108), ((float)UI::height / 108), -10.0f, 10.0f);
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, -10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glm::vec3 pos = glm::vec3(-4.0, -4.0, 0.0);
	float mvSpeed = 0.5f;
}

namespace Terrain {
	GLfloat rise = 1.0f;
	GLfloat segCount = 28;
	GLfloat xLength = 0.6f;
	GLfloat length = segCount * xLength;
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
	return;
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::string parentDir = getParentDirectory(argv[0]);

	GLSL_Idle Idle(parentDir + "//shaders//Idle.vert", parentDir + "//shaders//Idle.frag");
	GLSL_Flatscape Flatscape(parentDir + "//shaders//Flatscape.vert", parentDir + "//shaders//Flatscape.frag");

	GL4_DataSet square0(2, &square2D_Pos[0], sizeof(float) * 12);
	GL4_RigidLine rigidLine0(Terrain::rise, Terrain::segCount, Terrain::xLength, 0.4);
	Terrain::length = rigidLine0.get_length();
	rigidLine0.relMatrix = glm::translate(glm::mat4(1), glm::vec3(-1 * (Terrain::length / 2), 0.0, 0.0));
	GL4_RigidLine rigidLine1(Terrain::rise, 2.0f, Terrain::segCount, Terrain::xLength, 0.4);
	Terrain::length = rigidLine1.get_length();
	rigidLine1.relMatrix = glm::translate(glm::mat4(1), glm::vec3(-1 * (Terrain::length / 2), 0.0, 0.0));

	Time::sceneSetup = std::chrono::steady_clock::now();
	while(!glfwWindowShouldClose(window)){
		Time::sceneUpdate = std::chrono::steady_clock::now();
		Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::sceneUpdate - Time::sceneSetup);

		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(Flatscape.shaderProgID);
		Flatscape.set_mvpMatrix(Player::persMatrix * Player::viewMatrix * rigidLine0.relMatrix);

		glPointSize(8.0f);
		glLineWidth(11.0f);

		// Flatscape.set_renderMode(1);
		// square0.draw(GL_TRIANGLE_STRIP, 4);
		
		Flatscape.set_renderMode(0);
		// rigidLine1.drawFixed(GL_TRIANGLES, Time::secSpan.count() * 2);
		// rigidLine1.drawXI(GL_TRIANGLES, Time::secSpan.count() * 2);
		rigidLine1.drawXI(GL_TRIANGLE_STRIP, Time::secSpan.count() * 8);
		// rigidLine1.drawXI(GL_TRIANGLE_STRIP);
		Flatscape.set_renderMode(2);
		// rigidLine1.drawFixed(GL_POINTS, Time::secSpan.count() * 2);
		rigidLine1.drawXI(GL_POINTS, Time::secSpan.count() * 8);
		Flatscape.set_renderMode(1);
		rigidLine0.draw();

		glfwSwapBuffers(window);
	}

    glfwTerminate();
    return 0;
}
