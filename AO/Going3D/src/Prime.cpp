
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

noBlocks_UniformData noBlocks_Uniforms;

namespace Key {
	GLboolean W, A, S, D, J, I, K, O, L, P = false;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W && action == GLFW_PRESS) Key::W = true;
	if (key == GLFW_KEY_A && action == GLFW_PRESS) Key::A = true;
	if (key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
	if (key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
	if (key == GLFW_KEY_J && action == GLFW_PRESS) Key::J = true;
	if (key == GLFW_KEY_I && action == GLFW_PRESS) Key::I = true;
	if (key == GLFW_KEY_K && action == GLFW_PRESS) Key::K = true;
	if (key == GLFW_KEY_O && action == GLFW_PRESS) Key::O = true;
	if (key == GLFW_KEY_L && action == GLFW_PRESS) Key::L = true;
	if (key == GLFW_KEY_P && action == GLFW_PRESS) Key::P = true;
	if (key == GLFW_KEY_1 && action == GLFW_PRESS){
		std::cout << "Grey" << std::endl;
		noBlocks_Uniforms.defaultColor = { 0.5f, 0.5f, 0.5f, 0.8f };
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS){
		std::cout << "Hot" << std::endl;
		noBlocks_Uniforms.defaultColor = { 0.9607f, 0.6862f, 0.0f, 0.8f };
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS){
		std::cout << "Cool" << std::endl;
		noBlocks_Uniforms.defaultColor = {0.2588f, 0.5254f, 0.9568f, 0.8f};
	}
	if(key == GLFW_KEY_4 && action == GLFW_PRESS){
		std::cout << "Neutral" << std::endl;
		noBlocks_Uniforms.defaultColor = {0.3372f, 0.749f, 0.4862f, 0.8f};
	}

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) Key::W = false;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
	if (key == GLFW_KEY_J && action == GLFW_RELEASE) Key::J = false;
	if (key == GLFW_KEY_I && action == GLFW_RELEASE) Key::I = false;
	if (key == GLFW_KEY_K && action == GLFW_RELEASE) Key::O = false;
	if (key == GLFW_KEY_O && action == GLFW_RELEASE) Key::K = false;
	if (key == GLFW_KEY_L && action == GLFW_RELEASE) Key::L = false;
	if (key == GLFW_KEY_P && action == GLFW_RELEASE) Key::P = false;

	if(Key::W){
		std::cout << "Moving backwards" << std::endl;
		noBlocks_Uniforms.localMatrix = glm::translate(noBlocks_Uniforms.localMatrix, glm::vec3(0.0, 0.0, -0.5f));
	}
	if(Key::A){
		std::cout << "Moving left" << std::endl;
		noBlocks_Uniforms.localMatrix = glm::translate(noBlocks_Uniforms.localMatrix, glm::vec3(-0.5f, 0.0, 0.0));
	}
	if(Key::S){
		std::cout << "Moving forwards" << std::endl;
		noBlocks_Uniforms.localMatrix = glm::translate(noBlocks_Uniforms.localMatrix, glm::vec3(0.0, 0.0, 0.5f));
	}
	if(Key::D){
		std::cout << "Moving right" << std::endl;
		noBlocks_Uniforms.localMatrix = glm::translate(noBlocks_Uniforms.localMatrix, glm::vec3(0.5f, 0.0, 0.0));
	}
	
	if(Key::J){
		std::cout << "Negative rotation via X axis" << std::endl;
		noBlocks_Uniforms.localMatrix = glm::rotate(noBlocks_Uniforms.localMatrix, glm::radians(-5.0f), glm::vec3(1.0f, 0.0, 0.0));
	}
	if(Key::I){
		std::cout << "Positive rotation via X axis" << std::endl;
		noBlocks_Uniforms.localMatrix = glm::rotate(noBlocks_Uniforms.localMatrix, glm::radians(5.0f), glm::vec3(1.0f, 0.0, 0.0));
	}
	if(Key::K){
		std::cout << "Negative rotation via Y axis" << std::endl;
		noBlocks_Uniforms.localMatrix = glm::rotate(noBlocks_Uniforms.localMatrix, glm::radians(-5.0f), glm::vec3(0.0f, 1.0, 0.0));
	}
	if(Key::O){
		std::cout << "Positive rotation via Y axis" << std::endl;
		noBlocks_Uniforms.localMatrix = glm::rotate(noBlocks_Uniforms.localMatrix, glm::radians(5.0f), glm::vec3(0.0f, 1.0, 0.0));
	}
	if(Key::L){
		std::cout << "Negative rotation via Z axis" << std::endl;
		noBlocks_Uniforms.localMatrix = glm::rotate(noBlocks_Uniforms.localMatrix, glm::radians(-5.0f), glm::vec3(0.0f, 0.0, 1.0));
	}
	if(Key::P){
		std::cout << "Positive rotation via Z axis" << std::endl;
		noBlocks_Uniforms.localMatrix = glm::rotate(noBlocks_Uniforms.localMatrix, glm::radians(5.0f), glm::vec3(0.0f, 0.0, 1.0));
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

	if (glewInit() == GLEW_OK) std::cout << "GLEW initialized successfuly" << std::endl;
	else {
		std::cerr << "GLEW failed to initialize" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::string parentDir = getParentDirectory(argv[0]);

    std::string viewer3D_vert = parentDir + "\\shaders\\Viewer3D.vert";
    std::string viewer3D_frag = parentDir + "\\shaders\\Viewer3D.frag";
    GLuint viewer3D_glsl = compileShaders(viewer3D_vert, viewer3D_frag);

	std::string noBlocks_vert = parentDir + "\\shaders\\NoBlocks.vert";
    std::string noBlocks_frag = parentDir + "\\shaders\\NoBlocks.frag";
    GLuint noBlocks_glsl = compileShaders(noBlocks_vert, noBlocks_frag);

    ModelStatic Sponge;
    std::string spongeFilePath = parentDir + "\\data\\3D\\Sponge.obj";
	Sponge.renderParams[ShaderCtrlBit::color] = 0;

    assimpImportCPP(spongeFilePath, &Sponge);

	glUseProgram(noBlocks_glsl);

	noBlocks_Uniforms.worldMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 200.f);
	noBlocks_Uniforms.localMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, -5.0f));
    noBlocks_Uniforms.defaultColor = { 0.9607f, 0.6862f, 0.0f, 0.8f };
    noBlocks_Uniforms.surfaceRenderMode = 1;

	NoBlocks noBlocksUtil(noBlocks_glsl);
	noBlocksUtil.setUniforms(&noBlocks_Uniforms);

	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 0.88, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		noBlocksUtil.localMatrix(&noBlocks_Uniforms);
		noBlocksUtil.defaultColor(&noBlocks_Uniforms);

        glBindVertexArray(Sponge.VertexArray);
        glDrawElements(GL_TRIANGLES, Sponge.modelIndices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resources -- -- -- */

    glfwTerminate();
    return 0;
}
