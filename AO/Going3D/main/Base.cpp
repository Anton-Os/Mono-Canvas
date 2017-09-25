
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

namespace Key {
	GLboolean W, A, S, D = false;
}

namespace Player {
	GLboolean isGod = false;
	GLfloat height = 3.0f; 
	GLfloat movementSpeed = 10.0f / Globe::size;
	// GLuint steps = 100;
	GLuint steps = 100;
	GLuint yRotationSpeed = 120;
	GLuint xRotationSpeed = 90;
	glm::vec2 pos = glm::vec2(0.0, 0.0);
	glm::vec3 camera = glm::vec3(0.0, 0.0, Globe::size + Player::height);
	glm::vec3 lookPos = glm::vec3(0);
	glm::vec3 up = glm::vec3(0.0, 0.0, 1.0);
}

namespace Mouse {
	GLboolean appears = true;	
	GLdouble xInit, yInit;
	GLfloat xOffset, yOffset;
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos){

	if(Mouse::appears) Mouse::appears = false;
	else {
		if(xpos != Mouse::xInit) Mouse::xOffset -= GLfloat((xpos - Mouse::xInit) / Player::xRotationSpeed);
		if(ypos != Mouse::yInit) Mouse::yOffset -= GLfloat((ypos - Mouse::yInit) / Player::yRotationSpeed);

		std::cout << "Horizontal Angle: " << Mouse::xOffset << " Vertical Angle: " << Mouse::yOffset << std::endl;
	}

	Mouse::xInit = xpos;
	Mouse::yInit = ypos;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W && action == GLFW_PRESS) Key::W = true;
	if (key == GLFW_KEY_A && action == GLFW_PRESS) Key::A = true;
	if (key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
	if (key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		if(Player::isGod == true) Player::isGod = false;
		else Player::isGod = true;
	}

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) Key::W = false;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;

	if(Key::W) Player::pos.y += 1.0 / Player::steps;
	if(Key::A) Player::pos.x += 1.0 / Player::steps;
	if(Key::S) Player::pos.y -= 1.0 / Player::steps;
	if(Key::D) Player::pos.x -= 1.0 / Player::steps;
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
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);

	if (glewInit() == GLEW_OK) std::cout << "GLEW initialized successfuly" << std::endl;
	else {
		std::cerr << "GLEW failed to initialize" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::string parentDir = getParentDirectory(argv[0]);

	std::string litEnv_vert = parentDir + "\\shaders\\LitEnv.vert";
    std::string litEnv_frag = parentDir + "\\shaders\\LitEnv.frag";
	GLuint litEnv_glsl = compileShaders(litEnv_vert, litEnv_frag);
	std::string Sphere_vert = parentDir + "\\shaders\\Sphere.vert";
	std::string Sphere_frag = parentDir + "\\shaders\\Sphere.frag";
	GLuint Sphere_glsl = compileShaders(Sphere_vert, Sphere_frag);

	glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 10000.0f);
	glm::mat4 mvMatrix(1);

	glUseProgram(litEnv_glsl);
	LitEnv litEnvUtil(litEnv_glsl);
	litEnvUtil.initUniforms();

	glUseProgram(Sphere_glsl);
	Sphere sphereUtil(Sphere_glsl);
	sphereUtil.initUniforms();

	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resourcdes -- -- -- */

    glfwTerminate();
    return 0;
}
