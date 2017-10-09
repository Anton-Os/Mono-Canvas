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
	GLboolean W, A, S, D = false;
}

namespace Mouse {
	GLboolean appears = true;	
	GLdouble xInit, yInit;
	GLfloat xOffset, yOffset;
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
	// glfwSetKeyCallback(window, keyCallback);
	// glfwSetCursorPosCallback(window, cursorPosCallback);

	if (glewInit() == GLEW_OK) std::cout << "GLEW initialized successfuly" << std::endl;
	else {
		std::cerr << "GLEW failed to initialize" << std::endl;
		return -1;
	}

	// glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::string parentDir = getParentDirectory(argv[0]);

	GLuint testVAO;
	glGenVertexArrays(1, &testVAO);

	loadData(testVAO, sizeof(squarePos) / sizeof(GLfloat), GL_STATIC_DRAW, &squarePos[0], nullptr, nullptr, nullptr);
	loadIndices(testVAO, sizeof(squareIndices) / sizeof(GLuint), GL_STATIC_DRAW, &squareIndices[0]);

	std::string Locked_vert = parentDir + "//shaders//Locked.vert";
	std::string Locked_frag = parentDir + "//shaders//Locked.frag";
	GLuint Locked_uiID = compileShaders(Locked_vert, Locked_frag);
	glUseProgram(Locked_uiID);
	Locked Locked_glsl(Locked_uiID);
	Locked_glsl.initUniforms();

	//GL4_Sphere Sphere(100, 23, 20);
	GL4_BumpGrid BumpGrid(0.0, 100, 3, 100, 3);

	glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f);
	glm::mat4 mvMatrix(1);

	GLuint sphereDrawInterval = 50;
	GLuint sphereDrawFraction = 1;
	
	Time::sceneSetup = std::chrono::steady_clock::now();
	while(!glfwWindowShouldClose(window)){
		Time::sceneUpdate = std::chrono::steady_clock::now();
		Time::secSpan = std::chrono::duration_cast<std::chrono::duration<double>>(Time::sceneUpdate - Time::sceneSetup);

		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPointSize(10.0f);
		glLineWidth(4.0f);
		// Sphere.relMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -300.0f));
		// Locked_glsl.mvpMatrix(perspectiveMatrix * mvMatrix * Sphere.relMatrix);
		// Sphere.draw();
		// Sphere.drawFixed(GL_TRIANGLES, Time::secSpan.count() * 3 * 20); // Every Second 5 Triangles are drawn
		// Sphere.drawFixed(GL_LINES, Time::secSpan.count() * 2 * 50);
		BumpGrid.relMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, -200.0f));
		//BumpGrid.relMatrix *= glm::rotate(glm::mat4(1), glm::radians<float>(70.0), glm::vec3(1.0, 0.0, 0.0));
		Locked_glsl.mvpMatrix(perspectiveMatrix * mvMatrix * BumpGrid.relMatrix);
		// BumpGrid.draw(GL_LINES);
		// BumpGrid.drawFixed(GL_POINTS, Time::secSpan.count());
		// BumpGrid.drawFixed(GL_LINES, Time::secSpan.count() * 2);
		BumpGrid.drawFixed(GL_TRIANGLES, Time::secSpan.count() * 3 / 2);

        glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resourcdes -- -- -- */

    glfwTerminate();
    return 0;
}
