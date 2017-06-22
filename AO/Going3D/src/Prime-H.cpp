
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Common.h"

GLboolean cursorOn = true;
GLdouble cursorFirstX;
GLdouble cursorFirstY;

GLfloat cameraX = 0.0f;
GLfloat cameraY = 0.0f;
GLfloat cameraZ = -10.0f;

GLfloat lookX = 0.0;
GLfloat lookY = 0.0;
GLfloat lookZ = 0.0;

GLfloat inverseCameraX = cameraX - cameraX * 2;
GLfloat inverseCameraZ = cameraZ - cameraZ * 2;

// GLboolean Q, W, E, R, Y, U, P, A, S, D, F, H, J, N, M = false;
GLboolean Q, W, E, R, T, Y, U, I, O, P, A, S, D, F, G, H, J, K, L, Z, X, C, V, B, N, M = false;

const std::string getParentDirectory(const char* path) {
    const char* ptr = path + strlen(path);
    while (ptr != path && nullptr == strchr("\\/", *(--ptr)));
    std::size_t len = ptr - path;
    std::string result(path, len);
    std::cout << "Parent dir: " << result << std::endl;
    return result;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);

    if(key == GLFW_KEY_W && action == GLFW_PRESS) W = true;
    if(key == GLFW_KEY_A && action == GLFW_PRESS) A = true;
    if(key == GLFW_KEY_S && action == GLFW_PRESS) S = true;
    if(key == GLFW_KEY_D && action == GLFW_PRESS) D = true;
    
    if(key == GLFW_KEY_W && action == GLFW_RELEASE) W = false;
    if(key == GLFW_KEY_A && action == GLFW_RELEASE) A = false;
    if(key == GLFW_KEY_S && action == GLFW_RELEASE) S = false;
    if(key == GLFW_KEY_D && action == GLFW_RELEASE) D = false;

    if(W){ 
		cameraZ += 0.35f; 
	}
    if(A){ 
		cameraX += 0.35f; 
	}
    if(S){ 
		cameraZ -= 0.35f;
	}
    if(D){ 
		cameraX -= 0.35f;
	}

    std::cout << "X Position: " << cameraX << " Y Position: " << cameraY << " Z Position: " << cameraZ << std::endl;
	return;
}

void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	if (cursorOn) {
		cursorFirstX = xpos;
		cursorFirstY = ypos;
		cursorOn = false;
	}

	if(xpos > cursorFirstX){
		// lookX += (GLfloat)ypos / 4000;
		lookX += 0.35f;
		cursorFirstX = xpos; 
	}
	else if (xpos < cursorFirstX) {
		lookX -= 0.35f;
		cursorFirstX = xpos;
	}

	std::cout << "lookX is " << lookX << std::endl;
	std::cout << "Cursor initial X position was " << cursorFirstX << "and Cursor initial Y position was " << cursorFirstY << std::endl;
	std::cout << "Cursor current X position is " << xpos << " and Cursor current Y position is " << ypos << std::endl;

	return;
}

int main(int argc, const char* argv[]){
    if(glfwInit() == GLFW_FALSE){
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    } else {
        std::cout << "GLFW initialized!" << std::endl;
    }

	int WindowHeight = 700;
	int WindowWidth = 900;
    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // glfwWindowHint(GLFW_DECORATED, GL_TRUE);
    glViewport(0, 0, WindowWidth, WindowHeight);

    GLFWwindow* mainWindow = glfwCreateWindow(900, 700, "3D Cube Viewer", nullptr, nullptr);
    if(nullptr == mainWindow){
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(mainWindow);
    glfwGetFramebufferSize(mainWindow, &WindowWidth, &WindowHeight);
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(mainWindow, keyCallback);
	glfwSetCursorPosCallback(mainWindow, cursorCallback);

    if(glewInit() != GLEW_OK){
        std::cerr << "Failed to initialize GLEW" << std::endl;
    } else {
        std::cout << "GLEW initialized" << std::endl;
    }

    std::string parentDir(getParentDirectory(argv[0]));
    GLuint default_glsl = compileShaders(parentDir, "AO-8.vert", "AO-8.frag");
    GLuint viewer3D_glsl = compileShaders(parentDir, "Viewer3D.vert", "Viewer3D.frag");
    glUseProgram(viewer3D_glsl);

    glEnable(GL_DEPTH_TEST);

    struct Vertex {
        GLfloat pos[3];
        GLubyte color[4];
    };

    Vertex platform[] = {
        {{45.0f, 0.0, 45.0f}, {93, 109, 126, 255}},
        {{-45.0f, 0.0, 45.0f}, {93, 109, 126, 255}},
        {{45.0f, 0.0, -45.0f}, {93, 109, 126, 255}},
        {{-45.0f, 0.0, -45.0f}, {93, 109, 126, 255}}
    };

    Vertex cube[] = {
        {{ 1.0f, 1.0f, 1.0f }, { 84, 157, 234, 255 }},
        {{ -1.0f, 1.0f, 1.0f }, { 84, 157, 234, 255 }},
        {{ 1.0f, -1.0f, 1.0f }, { 84, 157, 234, 255 }},
        {{ -1.0f, -1.0f, 1.0f }, { 84, 157, 234, 255 }},

        {{ 1.0f, 1.0f, 1.0f }, { 251, 133, 133, 255 }},
        {{ 1.0f, -1.0f, 1.0f }, { 234, 84, 84, 255 }},
        {{ 1.0f, 1.0f, -1.0f }, { 234, 84, 84, 255 }},
        {{ 1.0f, -1.0f, -1.0f }, { 234, 84, 84, 255 }},

        {{ 1.0f, 1.0f, 1.0f }, { 138, 255, 177, 255 }},
        {{ 1.0f, 1.0f, -1.0f }, { 138, 255, 177, 255 }},
        {{ -1.0f, 1.0f, 1.0f }, { 138, 255, 177, 255 }},
        {{ -1.0f, 1.0f, -1.0f }, { 138, 255, 177, 255 }},

        {{ 1.0f, -1.0f, 1.0f }, { 255, 255, 159 , 255 }},
        {{ -1.0f, -1.0f, 1.0f }, { 255, 255, 159, 255 }},
        {{ 1.0f, -1.0, -1.0f }, { 255, 255, 159, 255 }},
        {{ -1.0f, -1.0f, -1.0f }, { 255, 255, 159, 255 }},

        {{ 1.0f, 1.0f, -1.0f }, { 178, 137, 204, 255 }},
        {{ 1.0f, -1.0f, -1.0f }, { 178, 137, 204, 255 }},
        {{ -1.0f, 1.0f, -1.0f }, { 178, 137, 204, 255 }},
        {{ -1.0f, -1.0f, -1.0f }, { 178, 137, 204, 255 }},

        {{ -1.0f, 1.0f, 1.0f }, { 255, 185, 95, 255 }},
        {{ -1.0f, 1.0f, -1.0f }, { 255, 185, 95, 255 }},
        {{ -1.0f, -1.0f, 1.0f }, { 255, 185, 95, 255 }},
        {{ -1.0f, -1.0f,-1.0f }, { 255, 185, 95, 255 }}
    };

    GLuint platformIndices[] = {
        0, 1, 2,
        3, 1, 2
    };

    GLuint cubeIndices[] = {
        0, 1, 2,
        2, 1, 3,
        4, 5, 6,
        6, 5, 7,
        8, 9, 10,
        10, 9, 11,
        12, 13, 14,
        14, 13, 15,
        16, 17, 18,
        18, 17, 19,
        20, 21, 22,
        22, 21, 23,
    };

	GLuint VertexArrayObjs[100];
	GLuint BufferObjs[100];
	GLuint usedBufferIndex = 0;

	glGenVertexArrays(100, VertexArrayObjs);
	glGenBuffers(100, BufferObjs);

	glBindVertexArray(VertexArrayObjs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, BufferObjs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(platform), platform, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));

	// glEnableVertexAttribArray(0);
	// glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferObjs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(platformIndices), platformIndices, GL_STATIC_DRAW);

	glBindVertexArray(VertexArrayObjs[1]);

	glBindBuffer(GL_ARRAY_BUFFER, BufferObjs[2]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferObjs[3]);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLint Projection = glGetUniformLocation(viewer3D_glsl, "Projection");
    GLint View = glGetUniformLocation(viewer3D_glsl, "View");
    GLint Model = glGetUniformLocation(viewer3D_glsl, "Model");

	glm::mat4 identityMatrix(1);
    glm::mat4 projectionMatrix(1);
	glm::mat4 lookAtMatrix(1);
	glm::mat4 viewMatrix(1);

    glm::mat4 platformMatrix(1);
    platformMatrix = glm::translate(identityMatrix, glm::vec3(0.0, -1.0f, 0.0));

    glm::mat4 cubeMatrix1(1);
	glm::mat4 cubeMatrix2(1);
	glm::mat4 cubeMatrix3(1);
	glm::mat4 cubeMatrix4(1);
	glm::mat4 cubeMatrix5(1);

    cubeMatrix1 = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
    cubeMatrix2 = glm::translate(identityMatrix, glm::vec3(6.0f, 6.0f, -20.0f));
    cubeMatrix3 = glm::translate(identityMatrix, glm::vec3(-6.0f, 6.0f, -20.0f));
    cubeMatrix4 = glm::translate(identityMatrix, glm::vec3(12.0f, 12.0f, -40.0f));
    cubeMatrix5 = glm::translate(identityMatrix, glm::vec3(-12.0f, 12.0f, -40.0f));

    glm::mat4 cubeMatrixArray[] = { cubeMatrix1,
									cubeMatrix2,
									cubeMatrix3,
									cubeMatrix4,
									cubeMatrix5 
	};

    projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 200.f);
	viewMatrix = glm::translate(identityMatrix, glm::vec3(cameraX, cameraY, cameraZ));

    while(!glfwWindowShouldClose(mainWindow)){
        glfwPollEvents();
        glClearColor(0.1294f, 0.1843f, 0.2352f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// viewMatrix = glm::rotate(viewMatrix, 0.02f, glm::vec3(lookX, lookY, 0.0)); 
		lookAtMatrix = glm::lookAt(
			glm::vec3(0.0, 0.0, 1.0),
			glm::vec3(lookX, lookY, 0.0),
			glm::vec3(0.0, 1.0, 0.0)
		);
		viewMatrix = glm::translate(lookAtMatrix, glm::vec3(cameraX, cameraY, cameraZ));
		// viewMatrix = viewMatrix * lookAtMatrix;

        glUniformMatrix4fv(Projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glUniformMatrix4fv(View, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(Model, 1, GL_FALSE, glm::value_ptr(platformMatrix));

		glBindVertexArray(VertexArrayObjs[0]);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
        glDrawElements(GL_TRIANGLES, sizeof(platformIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glBindVertexArray(VertexArrayObjs[1]);

		for (int cubeInstance = 0; cubeInstance < 5; cubeInstance++) {
			// viewMatrix = glm::translate(identityMatrix, glm::vec3(cameraX, cameraY, cameraZ));
			// viewMatrix = glm::rotate(identityMatrix, 0.02f, glm::vec3(lookX, lookY, 0.0));
			lookAtMatrix = glm::lookAt(
				glm::vec3(cameraX * -1.0f, cameraY * -1.0f, cameraZ * -1.0f),
				glm::vec3(lookX, lookY, 0.0),
				glm::vec3(0.0, 1.0, 0.0)
			);
			viewMatrix = glm::translate(lookAtMatrix, glm::vec3(cameraX, cameraY, cameraZ));
			// viewMatrix = viewMatrix * lookAtMatrix;

			glUniformMatrix4fv(Projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
			glUniformMatrix4fv(View, 1, GL_FALSE, glm::value_ptr(viewMatrix));
			glUniformMatrix4fv(Model, 1, GL_FALSE, glm::value_ptr(cubeMatrixArray[cubeInstance]));

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
		}

        glBindVertexArray(0);
        glfwSwapBuffers(mainWindow);
    }

    glfwTerminate();
    return 0;
}

