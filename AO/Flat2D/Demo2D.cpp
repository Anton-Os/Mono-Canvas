#include <iostream>
#include <string>
// #include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PipelineCtrl.h"
#include "Loaders.h"

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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::string parentDir = getParentDirectory(argv[0]);

	GLuint testVAO;
	glGenVertexArrays(1, &testVAO);
	#include "ManualEtrSets.h"
	loadData(testVAO, sizeof(squarePos) / sizeof(GLfloat), GL_STATIC_DRAW, &squarePos[0], nullptr, nullptr, nullptr);
	loadIndices(testVAO, sizeof(squareIndices) / sizeof(GLuint), GL_STATIC_DRAW, &squareIndices[0]);

	std::string Locked_vert = parentDir + "//shaders//Locked.vert";
	std::string Locked_frag = parentDir + "//shaders//Locked.frag";
	GLuint Locked_uiID = compileShaders(Locked_vert, Locked_frag);
	glUseProgram(Locked_uiID);
	Locked Locked_GLSL(Locked_uiID);
	Locked_GLSL.initUniforms();

	glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f);
	glm::mat4 mvMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, -10.0f));

	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Locked_GLSL.mvpMatrix(perspectiveMatrix * mvMatrix);

		glBindVertexArray(testVAO);
		glDrawElements(GL_TRIANGLES, sizeof(squareIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0); 
		// glDrawArrays(GL_LINES, 0, sizeof(squarePos) / sizeof(GLfloat));

        glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resourcdes -- -- -- */

    glfwTerminate();
    return 0;
}
