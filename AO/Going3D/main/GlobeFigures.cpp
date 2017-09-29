
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

namespace Globe {;
	GLfloat size = 100.0f;
	GLuint slices = 99;
	GLuint stacks = 100;
	GLboolean redraw = true;
	glm::mat4 rtRollMatrix(1);
	glm::mat4 rtYawMatrix(1);
}

namespace Player {
	GLboolean isGod = false;
	GLfloat height = 0.2f;
	// GLuint steps = 100;
	GLuint mvDegree = 100;
	std::array<GLint, 2> steps;
	GLuint yRotationSpeed = 120;
	GLuint xRotationSpeed = 90;
	glm::vec2 pos = glm::vec2(0.0, 0.0);
	glm::vec2 prevPos = glm::vec2(0.0, 0.0);
	glm::vec3 camera = glm::vec3(0.0, 0.0, Globe::size + Player::height);
	glm::vec3 lookPos = glm::vec3(0);
	glm::vec3 up = glm::vec3(0.0, 0.0, 1.0);
	glm::mat4 viewMatrix(1);
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

		// std::cout << "Horizontal Angle: " << Mouse::xOffset << " Vertical Angle: " << Mouse::yOffset << std::endl;
	}

	Mouse::xInit = xpos;
	Mouse::yInit = ypos;
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
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		if(Player::isGod == true) Player::isGod = false;
		else Player::isGod = true;
	}

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

	if(Key::W) Player::steps[0]++;
	if(Key::A) Player::steps[1]++;
	if(Key::S) Player::steps[0]--;
	if(Key::D) Player::steps[1]--;
	if(Key::Q) Player::mvDegree++;
	if(Key::E) Player::mvDegree--;
	if(Key::Q || Key::E) std::cout << "Player mvDegree: " << Player::mvDegree << std::endl;
	// if(Key::W || Key::S)
	Player::pos.x = Player::steps[0] * (2 * glm::pi<float>() / Player::mvDegree);
	// if(Key::A || Key::D)
	Player::pos.y = Player::steps[1] * ( 2 * glm::pi<float>() / Player::mvDegree);

	if(Key::O) Globe::slices++;
	if(Key::P) Globe::slices--;
	if(Key::K) Globe::stacks++;
	if(Key::L) Globe::stacks--;
	if(Key::O || Key::P || Key::K || Key::L){
		Globe::redraw = true;
		std::cout << "Size: " << Globe::size << " Slices: " << Globe::slices << " Stacks: " << Globe::stacks << std::endl;
	}
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
	glm::mat4 mvMatrix(1); glm::mat4 mvCentaur(1);

	glUseProgram(litEnv_glsl);
	LitEnv litEnvUtil(litEnv_glsl);
	litEnvUtil.initUniforms();

	std::vector<ModelComposite> Centaur;
    std::string Centaur_filePath = parentDir + "\\..\\..\\data\\Centaur.fbx";

    assimpImportCPP(Centaur_filePath, &Centaur);
	for(unsigned int mCount = 0; mCount < Centaur.size(); mCount++)
	// Centaur[mCount].relativePos = glm::translate(glm::mat4(1), glm::vec3(0.0, 1.0, 0.0) * Globe::size);
	// Centaur[mCount].relativePos = glm::scale(glm::mat4(1), glm::vec3(1000.0f, 1000.0f, 1000.0f)) * glm::translate(glm::mat4(1), glm::vec3(0.0, 1.0, 0.0) * Globe::size);
	
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
	std::array<GLuint, 2> sphereDrawVals;
	sphereUtil.renderMode(1);
	sphereUtil.colorPalette(&coolPalette);
	std::array<GLuint, 2> sphereParams = {Globe::slices, Globe::stacks};
	sphereUtil.sphereParams(sphereParams);
	std::array<GLfloat, 6> sphereGrad = { 
		coolPalette.color1[0], coolPalette.color1[1], coolPalette.color1[2],
		coolPalette.color2[0], coolPalette.color2[1], coolPalette.color2[2]
	};
	sphereUtil.gradient(sphereGrad);
	glBindTextureUnit(0, sphereTex);

	while(!glfwWindowShouldClose(window)){
		Player::prevPos = Player::pos;
		// Before variables are influenced by pollEvents

		glfwPollEvents();
		glClearColor(1.0, 1.0, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(Globe::redraw){
			sphereDrawVals = createSphere(Globe::size, Globe::slices, Globe::stacks);
			Globe::redraw = false;
		}

		Globe::rtYawMatrix = glm::rotate(glm::mat4(1), Player::pos.y, glm::vec3(0.0, 0.0, 1.0));
		Globe::rtRollMatrix = glm::rotate(glm::mat4(1), Player::pos.x, glm::vec3(1.0, 0.0, 0.0));

		// vMatrix = glm::lookAt(Player::camera, Player::lookPos, Player::up);
		if(!Player::isGod){
			Player::up = glm::vec3(0.0, 1.0, 0.0);
			Player::camera = (Player::up * Globe::size) + (Player::up * Player::height);
			Player::lookPos = glm::vec3(Player::camera.x, Player::camera.y, Player::camera.z - 1.0);
			Player::viewMatrix = glm::lookAt(Player::camera, Player::lookPos, Player::up);
			mvMatrix = Player::viewMatrix * Globe::rtYawMatrix * Globe::rtRollMatrix;
		} else {
			Player::up = glm::vec3(0.0, 1.0, 0.0);
			Player::camera = glm::vec3(0.0, 0.0, 1.0) * (Globe::size * 5);
			Player::lookPos = glm::vec3(Player::camera.x, Player::camera.y, Player::camera.z - 1.0);
			mvMatrix = Player::viewMatrix * Globe::rtYawMatrix * Globe::rtRollMatrix;
		}

		glUseProgram(Sphere_glsl);
		sphereUtil.mvpMatrix(perspectiveMatrix * mvMatrix);
		sphereUtil.nMatrix(glm::mat3(glm::transpose(glm::inverse(mvMatrix))));
		glBindVertexArray(sphereDrawVals[0]);
		glDrawElements(GL_TRIANGLES, sphereDrawVals[1], GL_UNSIGNED_INT, 0);

		Player::viewMatrix = glm::lookAt(Player::camera, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		glUseProgram(litEnv_glsl);
		mvMatrix = Globe::rtYawMatrix * Globe::rtRollMatrix;
		for(unsigned int mCount = 0; mCount < Centaur.size(); mCount++){
			Centaur[mCount].relativePos = glm::translate(glm::mat4(1), glm::vec3(0.0, 1.0, 0.0) * Globe::size) * mvMatrix;
			mvCentaur = Player::viewMatrix * Centaur.at(mCount).relativePos;
			// mvMatrix = Player::viewMatrix * glm::mat4(1);
			litEnvUtil.mvMatrix(mvCentaur);
			litEnvUtil.mvpMatrix(perspectiveMatrix * mvCentaur);
			litEnvUtil.nMatrix(glm::mat3(glm::transpose(glm::inverse(mvCentaur))));
			litEnvUtil.materialBlock(&Centaur.at(mCount).materialBlock);
			glBindVertexArray(Centaur[mCount].VertexArray);
			glDrawElements(GL_TRIANGLES, Centaur[mCount].modelIndices.size(), GL_UNSIGNED_INT, 0);
		}

        glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resourcdes -- -- -- */

    glfwTerminate();
    return 0;
}
