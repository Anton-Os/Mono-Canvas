/* #include <cmath>
#include <string>
#include <cstring>
#include <iostream> */

#include "Common.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const std::string getParentDirectory(const char* path) {
	const char* ptr = path + strlen(path);
	while (ptr != path && nullptr == strchr("\\/", *(--ptr)));
	std::size_t len = ptr - path;
	std::string result(path, len);
	std::cout << "Parent dir: " << result << std::endl;
	return result;
}

GLboolean W, A, S, D = false;

GLfloat cube1_X = 4.0f;
GLfloat cube1_Y = -10.0f;
GLfloat cube1_Z = -10.0f;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W && action == GLFW_PRESS) W = true;
	if (key == GLFW_KEY_A && action == GLFW_PRESS) A = true;
	if (key == GLFW_KEY_S && action == GLFW_PRESS) S = true;
	if (key == GLFW_KEY_D && action == GLFW_PRESS) D = true;

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) W = false;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) A = false;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) S = false;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) D = false;

	if (W) cube1_Y += 1.0f;
	if (A) cube1_X -= 1.0f;
	if (S) cube1_Y -= 1.0f;
	if (D) cube1_X += 1.0f;
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

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Lighting in 3D", nullptr, nullptr);
    if(nullptr != window) std::cout << "GLFW window created successfuly" << std::endl;
    else {
        std::cerr << "GLFW failed to create window" << std::endl;
        return -1;
    }

	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
	glfwSetKeyCallback(window, keyCallback);

	if (glewInit() == GLEW_OK) std::cout << "GLEW initialized successfuly" << std::endl;
	else {
		std::cerr << "GLEW failed to initialize" << std::endl;
		return -1;
	}
    
    /* -- -- -- Reference to other local .cpp files, creating/loading data to be used in the game loop -- -- -- */
	std::string parentDir = getParentDirectory(argv[0]);
	
	GLuint litEnvGLSL = compileShaders(parentDir, "LitEnv.vert", "LitEnv.frag");
    GLuint simpleDiffuseGLSL = compileShaders(parentDir, "SimpleDiffuse.vert", "SimpleDiffuse.frag");
    
	glEnable(GL_DEPTH_TEST);
	// glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	GLenum errorCheck1_OpenGL = glGetError();

    struct Vertex {
        GLfloat pos[3];
        GLubyte color[4];
    };

    Vertex cube[] = {
		{ { 1.0f, 1.0f, 1.0f }, { 84, 157, 234, 255 } },
		{ { -1.0f, 1.0f, 1.0f }, { 84, 157, 234, 255 } },
		{ { 1.0f, -1.0f, 1.0f }, { 84, 157, 234, 255 } },
		{ { -1.0f, -1.0f, 1.0f }, { 84, 157, 234, 255 } },

		{ { 1.0f, 1.0f, 1.0f }, { 251, 133, 133, 255 } },
		{ { 1.0f, -1.0f, 1.0f }, { 234, 84, 84, 255 } },
		{ { 1.0f, 1.0f, -1.0f }, { 234, 84, 84, 255 } },
		{ { 1.0f, -1.0f, -1.0f }, { 234, 84, 84, 255 } },

		{ { 1.0f, 1.0f, 1.0f }, { 138, 255, 177, 255 } },
		{ { 1.0f, 1.0f, -1.0f }, { 138, 255, 177, 255 } },
		{ { -1.0f, 1.0f, 1.0f }, { 138, 255, 177, 255 } },
		{ { -1.0f, 1.0f, -1.0f }, { 138, 255, 177, 255 } },

		{ { 1.0f, -1.0f, 1.0f }, { 255, 255, 159 , 255 } },
		{ { -1.0f, -1.0f, 1.0f }, { 255, 255, 159, 255 } },
		{ { 1.0f, -1.0, -1.0f }, { 255, 255, 159, 255 } },
		{ { -1.0f, -1.0f, -1.0f }, { 255, 255, 159, 255 } },

		{ { 1.0f, 1.0f, -1.0f }, { 178, 137, 204, 255 } },
		{ { 1.0f, -1.0f, -1.0f }, { 178, 137, 204, 255 } },
		{ { -1.0f, 1.0f, -1.0f }, { 178, 137, 204, 255 } },
		{ { -1.0f, -1.0f, -1.0f }, { 178, 137, 204, 255 } },

		{ { -1.0f, 1.0f, 1.0f }, { 255, 185, 95, 255 } },
		{ { -1.0f, 1.0f, -1.0f }, { 255, 185, 95, 255 } },
		{ { -1.0f, -1.0f, 1.0f }, { 255, 185, 95, 255 } },
		{ { -1.0f, -1.0f,-1.0f }, { 255, 185, 95, 255 } }
	};

	GLfloat cubeNormals[] = {
		0, 0, 1.0f,
		0, 0, 1.0f,
		0, 0, 1.0f,
		0, 0, 1.0f,

		1.0f, 0, 0,
		1.0f, 0, 0,
		1.0f, 0, 0,
		1.0f, 0, 0,

		0, 1.0f, 0,
		0, 1.0f, 0,
		0, 1.0f, 0,
		0, 1.0f, 0,

		0, -1.0f, 0,
		0, -1.0f, 0,
		0, -1.0f, 0,
		0, -1.0f, 0,

		0, 0, -1.0f,
		0, 0, -1.0f,
		0, 0, -1.0f,
		0, 0, -1.0f,

		-1.0f, 0, 0,
		-1.0f, 0, 0,
		-1.0f, 0, 0,
		-1.0f, 0, 0,
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
    /* -- -- -- Populating OpenGL Buffers -- -- -- */
    GLuint VAOs[100];
    GLuint VBOs[100];

    glGenVertexArrays(100, VAOs);
    glGenBuffers(100, VBOs);
    
    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLenum errorCheck2_OpenGL = glGetError();
    /* -- -- -- Locating uniform variables within shader prog -- -- -- */
        // Vertex Shader Uniforms
    GLint simpleDiffuseGLSL_World = glGetUniformLocation(simpleDiffuseGLSL, "World");
    GLint simpleDiffuseGLSL_Local = glGetUniformLocation(simpleDiffuseGLSL, "Local");
        // Fragment Shader Uniforms
    GLint simpleDiffuseGLSL_ambientLightStrength = glGetUniformLocation(simpleDiffuseGLSL, "ambientLightStrength");
    GLint simpleDiffuseGLSL_worldLightColor = glGetUniformLocation(simpleDiffuseGLSL, "worldLightColor");
    GLint simpleDiffuseGLSL_lightSourcePos = glGetUniformLocation(simpleDiffuseGLSL, "lightSourcePos");

    GLenum errorCheck3_OpenGL = glGetError();
    /* -- -- -- Specifying uniform data -- -- -- */
    glm::vec3 cameraPos(1);
    glm::vec3 cube1_Origin(1);

    glm::mat4 projectionMatrix(1);
    glm::mat4 viewMatrix(1);
    glm::mat4 worldMatrix(1); // Applies to all models in world
	
    glm::mat4 localMatrix(1); // To handle changes specific to model
    glm::mat4 cube1_Matrix(1);

    cameraPos = glm::vec3(0, 0, 0);

    projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 200.f);

    GLfloat ambientLightStrength = 0.5f;
    GLfloat worldLightColor[3] = { 1.0f, 1.0f, 1.0f };
    GLfloat lightSourcePos[3] = { 0, 10.0f, 0 };

    /* -- -- -- Executing infinite game loop -- -- -- */
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(worldLightColor[0] * ambientLightStrength,
                     worldLightColor[1] * ambientLightStrength,
                     worldLightColor[2] * ambientLightStrength,
                     1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* -- -- -- Commands specific to the current shader program in use -- -- -- */
        glUseProgram(simpleDiffuseGLSL);

		cube1_Origin = glm::vec3(cube1_X, cube1_Y, cube1_Z);

        // viewMatrix is recomputed on every iteration of while loop
		viewMatrix = glm::lookAt(cameraPos, cube1_Origin, glm::vec3(0.0, 1.0f, 0.0));
        worldMatrix = projectionMatrix * viewMatrix;

        glUniformMatrix4fv(simpleDiffuseGLSL_World, 1, GL_FALSE, glm::value_ptr(worldMatrix));

        glUniform1f(simpleDiffuseGLSL_ambientLightStrength, ambientLightStrength);
        glUniform3fv(simpleDiffuseGLSL_worldLightColor, 1, worldLightColor);
        glUniform3fv(simpleDiffuseGLSL_lightSourcePos, 1, lightSourcePos);

        /* -- -- -- Commands specific to the current draw being performed -- */
        glBindVertexArray(VAOs[0]);

		cube1_Matrix = glm::translate(glm::mat4(1), cube1_Origin);
        localMatrix = cube1_Matrix;

        glUniformMatrix4fv(simpleDiffuseGLSL_Local, 1, GL_FALSE, glm::value_ptr(localMatrix));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(3);
        glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLubyte), GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(3);

        glBindVertexArray(0);
        glfwSwapBuffers(window);    
    }
    /* -- -- -- Deallocation and deletion of resources -- -- -- */
    glDeleteProgram(simpleDiffuseGLSL);
    glDeleteVertexArrays(100, VAOs);
    glDeleteBuffers(100, VBOs);
    
    glfwTerminate();
    return 0;
}
