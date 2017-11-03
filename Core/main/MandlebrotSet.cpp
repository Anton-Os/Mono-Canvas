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

namespace Camera {
	// glm::mat4 perspectiveMatrix = glm::ortho(-1 * ((float)UI::width / 108), ((float)UI::width / 108), -1 * ((float)UI::height / 108), ((float)UI::height / 108), -10.0f, 10.0f);
	glm::mat4 perspectiveMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -10.0f, 10.0f);
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glm::vec3 pos = glm::vec3(-4.0, -4.0, 0.0);
	float mvSpeed = 0.5f;
}

namespace Time {
	std::chrono::steady_clock::time_point sceneSetup;
	std::chrono::steady_clock::time_point sceneUpdate;
	std::chrono::duration<double> secSpan;
	std::chrono::duration<double, std::milli> milliSpan;
	std::chrono::duration<double, std::micro> microSpan;
	std::chrono::duration<double, std::nano> nanoSpan;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
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
	glfwSetKeyCallback(window, keyCallback);

	if (glewInit() == GLEW_OK) std::cout << "GLEW initialized successfuly" << std::endl;
	else {
		std::cerr << "GLEW failed to initialize" << std::endl;
		return -1;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::string parentDir = getParentDirectory(argv[0]);

	GLSL_Idle Idle(parentDir + "//shaders//Idle.vert", parentDir + "//shaders//Idle.frag");
	GLSL_Fractals Fractals(parentDir + "//shaders//Fractals.vert", parentDir + "//shaders//Fractals.frag");

	GL4_DataSet square(2, &square2D_Pos[0], sizeof(float) * 9);

	Time::sceneSetup = std::chrono::steady_clock::now();
	while(!glfwWindowShouldClose(window)){
		Time::sceneUpdate = std::chrono::steady_clock::now();
		Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::sceneUpdate - Time::sceneSetup);

		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(Fractals.shaderProgID);
		Fractals.set_mvpMatrix(Camera::perspectiveMatrix * Camera::viewMatrix);
		Fractals.set_iterCount(80);

		/* glUseProgram(Idle.shaderProgID);
		Idle.set_mvpMatrix(Camera::perspectiveMatrix * Camera::viewMatrix);
		Idle.set_renderMode(0); */
		square.draw(GL_TRIANGLE_STRIP, 4);

		glPointSize(8.0f);
		glLineWidth(11.0f);
		
		glfwSwapBuffers(window);
	}

    glfwTerminate();
    return 0;
}
