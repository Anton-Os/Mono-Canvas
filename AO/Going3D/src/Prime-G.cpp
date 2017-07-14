
#include "Common.h"
#include "Assimp.h"

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

GLfloat cube1_X = 0.0;
GLfloat cube1_Y = 0.0;
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

	if (W) cube1_Y += 0.3f;
	if (A) cube1_X -= 0.3f;
	if (S) cube1_Y -= 0.3f;
	if (D) cube1_X += 0.3f;
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

    if(glewGetExtension("GL_ARB_gl_spirv") == GL_TRUE) std::cout << "SPIRV extension was fetched" << std::endl;
    else {
        std::cout << "SPIRV failed you idiot" << std::endl;
    }
    
    /* -- -- -- Reference to other local .cpp files, creating/loading data to be used in the game loop -- -- -- */
	std::string parentDir = getParentDirectory(argv[0]);
	
	GLuint litEnvGLSL = compileShaders(parentDir, "LitEnv.vert", "LitEnv.frag");
	GLuint originalDiffuseGLSL = compileShaders(parentDir, "OriginalDiffuse.vert", "OriginalDiffuse.frag");
    GLuint simpleDiffuseGLSL = compileShaders(parentDir, "SimpleDiffuse.vert", "SimpleDiffuse.frag");
    
	glEnable(GL_DEPTH_TEST);


    /* -- -- -- Locating uniform variables within shader prog -- -- -- */
        // Vertex Shader Uniforms
    GLint simpleDiffuseGLSL_World = glGetUniformLocation(simpleDiffuseGLSL, "World");
    GLint simpleDiffuseGLSL_Local = glGetUniformLocation(simpleDiffuseGLSL, "Local");
        // Fragment Shader Uniforms
    GLint simpleDiffuseGLSL_ambientLightStrength = glGetUniformLocation(simpleDiffuseGLSL, "ambientLightStrength");
    GLint simpleDiffuseGLSL_cameraPos = glGetUniformLocation(simpleDiffuseGLSL, "cameraPos");
	GLint simpleDiffuseGLSL_worldLightColor = glGetUniformLocation(simpleDiffuseGLSL, "worldLightColor");
    GLint simpleDiffuseGLSL_lightSourcePos = glGetUniformLocation(simpleDiffuseGLSL, "lightSourcePos");

    GLenum errorCheck3_OpenGL = glGetError();
    /* -- -- -- Specifying uniform data -- -- -- */
    glm::vec3 cameraPos(1);

    glm::mat4 projectionMatrix(1);
    glm::mat4 viewMatrix(1);

    glm::mat4 worldMatrix(1); // Applies to all models in world
    glm::mat4 localMatrix(1); // To handle changes specific to model

    cameraPos = glm::vec3(0, 0, -20.0f);
    projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 200.f);
	viewMatrix = glm::lookAt(cameraPos, glm::vec3(0, 0, 0), glm::vec3(0, 1.0, 0));

    GLfloat ambientLightStrength = 0.7f;
    GLfloat worldLightColor[3] = { 1.0f, 1.0f, 1.0f };
    GLfloat lightSourcePos[3] = { 1.0f, 10.0f, -10.0f };

	worldMatrix = projectionMatrix * viewMatrix;
	
	glUniformMatrix4fv(simpleDiffuseGLSL_World, 1, GL_FALSE, glm::value_ptr(worldMatrix));
	glUniformMatrix4fv(simpleDiffuseGLSL_Local, 1, GL_FALSE, glm::value_ptr(localMatrix));

	glUniform1f(simpleDiffuseGLSL_ambientLightStrength, ambientLightStrength);
    glUniform3fv(simpleDiffuseGLSL_cameraPos, 1, glm::value_ptr(cameraPos));
    glUniform3fv(simpleDiffuseGLSL_worldLightColor, 1, worldLightColor);
    glUniform3fv(simpleDiffuseGLSL_lightSourcePos, 1, lightSourcePos);

    std::string deadEngineSTP = "\\data\\3D\\RECARO.stl";
    std::string deadEngine = parentDir + deadEngineSTP;
	Model3D* DeadEngine = new Model3D(simpleDiffuseGLSL, parentDir, deadEngineSTP);
	while(! glfwWindowShouldClose){
        DeadEngine->renderScene();
	}

    /* -- -- -- Deallocation and deletion of resources -- -- -- */
	delete DeadEngine;
    glDeleteProgram(simpleDiffuseGLSL);

    glfwTerminate();
    return 0;
}
