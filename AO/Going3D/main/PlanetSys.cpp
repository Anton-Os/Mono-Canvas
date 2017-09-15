
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
	GLboolean W, A, S, D, Q, E, O, P, K, L = false;
}

namespace Player {
	GLfloat height = 3.0f; 
	GLfloat movementSpeed = 10.0f;
	GLuint vRotationSpeed = 120;
	GLuint hRotationSpeed = 90;
}

namespace Globe {
	GLfloat size = 600.0f;
	GLuint slices = 300;
	GLuint stacks = 300;
}

// glm::vec3 cameraPos = glm::vec3(0.0, 0.0, -300.0f);
glm::vec3 cameraPos = glm::vec3(0.0, Globe::size + Player::height, 0.0f);
glm::mat4 cameraRotation(1);
GLboolean cursorPresent = true;	
GLdouble cursorInitX, cursorInitY;
GLfloat hAngle, vAngle;

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos){

	if(cursorPresent) cursorPresent = false;
	else {
		if(xpos != cursorInitX) hAngle -= GLfloat((xpos - cursorInitX) / Player::hRotationSpeed);
		if(ypos != cursorInitY) vAngle -= GLfloat((ypos - cursorInitY) / Player::vRotationSpeed);

		std::cout << "Horizontal Angle: " << hAngle << " Vertical Angle: " << vAngle << std::endl;
	}

	cursorInitX = xpos;
	cursorInitY = ypos;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W && action == GLFW_PRESS) Key::W = true;
	if (key == GLFW_KEY_A && action == GLFW_PRESS) Key::A = true;
	if (key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
	if (key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) Key::Q = true;
	if (key == GLFW_KEY_E && action == GLFW_PRESS) Key::E = true;
	if (key == GLFW_KEY_O && action == GLFW_PRESS) Key::O = true;
	if (key == GLFW_KEY_P && action == GLFW_PRESS) Key::P = true;
	if (key == GLFW_KEY_K && action == GLFW_PRESS) Key::K = true;
	if (key == GLFW_KEY_L && action == GLFW_PRESS) Key::L = true;

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) Key::W = false;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE) Key::Q = false;
	if (key == GLFW_KEY_E && action == GLFW_RELEASE) Key::E = false;
	if (key == GLFW_KEY_O && action == GLFW_RELEASE) Key::O = false;
	if (key == GLFW_KEY_P && action == GLFW_RELEASE) Key::P = false;
	if (key == GLFW_KEY_K && action == GLFW_RELEASE) Key::K = false;
	if (key == GLFW_KEY_L && action == GLFW_RELEASE) Key::L = false;

	if(Key::W) cameraPos.z += Player::movementSpeed; 
	if(Key::A) cameraPos.x += Player::movementSpeed;
	if(Key::S) cameraPos.z -= Player::movementSpeed;
	if(Key::D) cameraPos.x -= Player::movementSpeed;
	if(Key::Q) cameraPos.y -= Player::movementSpeed;
	if(Key::E) cameraPos.y += Player::movementSpeed;
	if(Key::O) Globe::slices++;
	if(Key::P) Globe::slices--;
	if(Key::K) Globe::stacks++;
	if(Key::L) Globe::stacks--;
	if(Key::O || Key::P || Key::K || Key::L) 
	std::cout << "Size: " << Globe::size << " Slices: " << Globe::slices << " Stacks: " << Globe::stacks << std::endl;
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

    std::vector<ModelComposite> MPerComponent;
    std::string LowPolyMill_filePath = parentDir + "\\..\\..\\data\\LowPolyMill.fbx";

    assimpImportCPP(LowPolyMill_filePath, &MPerComponent);

	glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1500.0f);
	glm::mat4 mvMatrix(1);
	glm::vec3 lookPos(1);

	glUseProgram(litEnv_glsl);
	LitEnv litEnvUtil(litEnv_glsl);
	litEnvUtil.initUniforms();

	glUseProgram(Sphere_glsl);
	Sphere sphereUtil(Sphere_glsl);
	sphereUtil.initUniforms();

	ColorPalette4x3 warmPalette {
		{1.0f, 0.313f, 0.313f},
		{1.0f, 0.6f, 0.4f},
		{1.0f, 0.701f, 0.854f},
		{1.0f, 1.0f, 0.6f},
	};

	ColorPalette4x3 coolPalette {
		{0.219f, 0.447f, 0.819f},
		{0.243f, 0.4f, 0.76f},
		{0.466f, 0.615f, 0.819f},
		{0.76f, 0.913f, 0.96f}
	};

	std::string sphereTex_filePath = parentDir + "\\..\\..\\data\\SandTex1.ktx";
	GLuint sphereTex = createTexture(sphereTex_filePath.c_str());

	ModelComposite Sphere;
	createSphere(&Sphere, Globe::size, Globe::slices, Globe::stacks);

	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lookPos = glm::vec3(cameraPos.x + std::sin(hAngle), cameraPos.y + std::sin(vAngle), cameraPos.z + std::cos(hAngle + vAngle));
		mvMatrix = glm::lookAt(cameraPos, lookPos, glm::vec3(0.0, 1.0, 0.0));

		sphereUtil.mvpMatrix(perspectiveMatrix * mvMatrix);
		sphereUtil.nMatrix(glm::mat3(glm::transpose(glm::inverse(mvMatrix))));
		sphereUtil.renderMode(2);
		sphereUtil.colorPalette(&coolPalette);
		glBindTextureUnit(0, sphereTex);
		glBindVertexArray(Sphere.VertexArray);
		glDrawElements(GL_TRIANGLES, Sphere.modelIndices.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resources -- -- -- */

    glfwTerminate();
    return 0;
}
