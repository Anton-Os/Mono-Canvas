
#include "Common.h"
// #include "Assimp.h"

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

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W && action == GLFW_PRESS) W = true;
	if (key == GLFW_KEY_A && action == GLFW_PRESS) A = true;
	if (key == GLFW_KEY_S && action == GLFW_PRESS) S = true;
	if (key == GLFW_KEY_D && action == GLFW_PRESS) D = true;

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) W = false;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) A = false;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) S = false;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) D = false;
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

	std::string parentDir = getParentDirectory(argv[0]);

	std::string recaroModel = parentDir + "\\data\\3D\\RECARO.stl";
	std::string polyMillModel = parentDir + "\\data\\3D\\low-poly-mill.obj";
    std::string spongeModel = parentDir + "\\data\\3D\\Sponge.obj";
    std::vector<Point> meshes;
	std::vector<GLuint> indices;

	GLuint modelStatic_glsl = compileShaders(parentDir, "shaders\\ModelStatic.vert", "shaders\\ModelStatic.frag");
    
	ModelStatic Sponge = {
		spongeModel, meshes, indices
	};

	// assimpImportCPP(spongeModel);
    assimpImportCPP(Sponge);

	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 0.88, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(modelStatic_glsl);
        // glDrawArrays(GL_TRIANGLES, 0, 50);
        glDrawElements(GL_TRIANGLES, 800, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resources -- -- -- */

    glfwTerminate();
    return 0;
}
