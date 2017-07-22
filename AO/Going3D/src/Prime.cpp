
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

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Asset Import", nullptr, nullptr);
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

	/* std::string recaroModel = parentDir + "\\data\\3D\\RECARO.stl";
	std::string polyMillModel = parentDir + "\\data\\3D\\low-poly-mill.obj"; */

    std::string spongeModel = parentDir + "\\data\\3D\\Sponge.obj";
    GLuint VertexArrayID;
    std::vector<Point> meshes;
	std::vector<GLuint> indices;

    // GLuint modelStatic_glsl = compileShaders(parentDir, "shaders\\ModelStatic.vert", "shaders\\ModelStatic.frag");
    std::string modelStatic_vert = parentDir + "\\shaders\\ModelStatic.vert";
    std::string modelStatic_frag = parentDir + "\\shaders\\ModelStatic.frag";
    GLuint modelStatic_glsl = compileShaders(modelStatic_vert, modelStatic_frag);

	ModelStatic Sponge = {
        spongeModel, VertexArrayID, meshes, indices
	};

	assimpImportCPP(&Sponge);

	GLuint modelStatic_vert_uniformBlockID = glGetUniformBlockIndex(modelStatic_glsl, "vertexBlock");
	GLuint modelStatic_frag_uniformBlockID = glGetUniformBlockIndex(modelStatic_glsl, "fragmentBlock");

	if(modelStatic_vert_uniformBlockID == GL_INVALID_INDEX) 
	std::cerr << "Uniform block vertexBlock does not exist in shader file " << modelStatic_vert << std::endl;

	if(modelStatic_frag_uniformBlockID == GL_INVALID_INDEX) 
	std::cerr << "Uniform block fragBlock does not exist in shader file " << modelStatic_frag << std::endl;

	struct modelStatic_vert_uniformData {
		glm::mat4 worldMatrix;
		glm::mat4 localMatrix;
	};

	struct modelStatic_frag_uniformData {
		GLfloat ambientLightStrength;
		GLuint surfaceRenderMode;
	};

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 200.f);
	glm::mat4 view = glm::mat4(1);

	glm::mat4 worldMatrix = projection * view;
	glm::mat4 sponge_localMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, -5.0f));

	modelStatic_vert_uniformData vertexBlock = {
		worldMatrix,
		sponge_localMatrix,
	};

	modelStatic_frag_uniformData fragmentBlock = {
		1.0f,
		0
	};

	glUniformBlockBinding(modelStatic_vert_uniformBlockID, modelStatic_glsl, 0);
	glUniformBlockBinding(modelStatic_frag_uniformBlockID, modelStatic_glsl, 1);

	GLuint UBO[2];
	glGenBuffers(2, UBO);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO[0]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(vertexBlock), &vertexBlock, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO[0]);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO[1]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(fragmentBlock), &fragmentBlock, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, UBO[1]);


	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 0.88, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(modelStatic_glsl);
        // glDrawArrays(GL_TRIANGLES, 0, 50);

        glBindVertexArray(Sponge.VertexArray);
        glDrawElements(GL_TRIANGLES, Sponge.modelIndices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resources -- -- -- */

    glfwTerminate();
    return 0;
}
