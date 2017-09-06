
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
	GLboolean W, A, S, D, Q, E = false;
}

glm::vec3 cameraPos = glm::vec3(0.0, 0.0, -100.0f);
glm::mat4 cameraRotation(1);
GLboolean cursorPresent = true;
GLdouble cursorInitX, cursorInitY;
GLfloat hAngle, vAngle;
// camRoll = 1.0;
GLfloat movementSpeed = 10.0f;

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos){

	if(cursorPresent) cursorPresent = false;
	else {
		if(xpos != cursorInitX) hAngle -= GLfloat((xpos - cursorInitX) / 90);
		if(ypos != cursorInitY) vAngle -= GLfloat((ypos - cursorInitY) / 90);

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

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) Key::W = false;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE) Key::Q = false;
	if (key == GLFW_KEY_E && action == GLFW_RELEASE) Key::E = false;

	if(Key::W) cameraPos.z += movementSpeed; 
	if(Key::A) cameraPos.x += movementSpeed;
	if(Key::S) cameraPos.z -= movementSpeed;
	if(Key::D) cameraPos.x -= movementSpeed;
	if(Key::Q) cameraPos.y -= movementSpeed;
	if(Key::E) cameraPos.y += movementSpeed;
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
	// GLuint error;
	// GLuint occQuery[10];
	// GLuint64 occQueryResult[10];
	// glGenQueries(10, occQuery);

	std::string parentDir = getParentDirectory(argv[0]);

	std::string litEnv_vert = parentDir + "\\shaders\\LitEnv.vert";
    std::string litEnv_frag = parentDir + "\\shaders\\LitEnv.frag";
	// std::string litEnv_vert = parentDir + "\\shaders\\V-Instanced.vert";
	// std::string litEnv_frag = parentDir + "\\shaders\\V-Instanced.frag";
    GLuint litEnv_glsl = compileShaders(litEnv_vert, litEnv_frag);
	std::string Sphere_vert = parentDir + "\\shaders\\Sphere.vert";
	std::string Sphere_frag = parentDir + "\\shaders\\Sphere.frag";
	GLuint Sphere_glsl = compileShaders();

    std::vector<ModelComposite> MPerComponent;
    std::string LowPolyMill_filePath = parentDir + "\\..\\..\\data\\LowPolyMill.fbx";
	// std::string LowPolyMill_filePath = parentDir + "\\..\\..\\data\\KSR-29-SniperRifle.fbx";

    assimpImportCPP(LowPolyMill_filePath, &MPerComponent);

	glUseProgram(litEnv_glsl);

	glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.f);
	glm::mat4 mvMatrix(1);
	glm::vec3 lookPos(1);

	LitEnv litEnvUtil(litEnv_glsl);
	litEnvUtil.initUniforms();

	// error = glGetError();
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
        glClearColor(1.0f, 1.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lookPos = glm::vec3(cameraPos.x + std::sin(hAngle), cameraPos.y + std::sin(vAngle), cameraPos.z + std::cos(hAngle + vAngle));
		mvMatrix = glm::lookAt(cameraPos, lookPos, glm::vec3(0.0, 1.0, 0.0));

        for(unsigned int d = 0; d < MPerComponent.size(); d++){
            if(MPerComponent.at(d).renderParams[ShaderCtrlBit::drawable] == 1){
				// mvMatrix *= glm::translate(glm::mat4(1), cameraPos) * MPerComponent.at(d).relativePos;
				litEnvUtil.mvMatrix(mvMatrix);
				litEnvUtil.mvpMatrix(perspectiveMatrix * mvMatrix);
				litEnvUtil.nMatrix(glm::mat3(glm::transpose(glm::inverse(mvMatrix))));
				litEnvUtil.materialBlock(&MPerComponent.at(d).materialBlock);
                glBindVertexArray(MPerComponent.at(d).VertexArray);
				
				// glBeginQuery(GL_PRIMITIVES_GENERATED, occQuery[d]);
				glDrawElements(GL_TRIANGLES, MPerComponent.at(d).modelIndices.size(), GL_UNSIGNED_INT, 0);
				// glEndQuery(GL_PRIMITIVES_GENERATED);
				// glGetQueryObjectui64v(occQuery[d], GL_QUERY_RESULT, &occQueryResult[d]);
			}
		}
        glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resources -- -- -- */

    glfwTerminate();
    return 0;
}
