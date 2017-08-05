
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
GLfloat rotateAngleX, rotateAngleY, rotateAngleZ;

namespace Key {
	GLboolean W, A, S, D, Q, E, H, U, J, I, K, O, L, P = false;
}

glm::vec3 camMovement = glm::vec3(0.0, 0.0, -100.0f);
glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.f);

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

	if(Key::W) camMovement.z += 3.0f; 
	if(Key::A) camMovement.x += 1.0f; 
	if(Key::S) camMovement.z -= 3.0f; 
	if(Key::D) camMovement.x -= 1.0f; 
	if(Key::Q) camMovement.y -= 1.0f; 
	if(Key::E) camMovement.y += 1.0f; 
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

	std::string noBlocks_vert = parentDir + "\\shaders\\LitBlocks.vert";
    std::string noBlocks_frag = parentDir + "\\shaders\\LitBlocks.frag";
    GLuint noBlocks_glsl = compileShaders(noBlocks_vert, noBlocks_frag);

    std::vector<ModelComposite> MPerComponent;
    std::string LowPolyMill_filePath = parentDir + "\\data\\LowPolyMill.fbx";

    assimpImportCPP(LowPolyMill_filePath, &MPerComponent);

	glUseProgram(noBlocks_glsl);

	noBlocks_Uniforms.worldMatrix = perspectiveMatrix;
	noBlocks_Uniforms.defaultColor = { 0.9607f, 0.6862f, 0.0f, 0.8f };
    noBlocks_Uniforms.surfaceRenderMode = 0;

	NoBlocks noBlocksUtil(noBlocks_glsl);
    noBlocksUtil.setUniforms(&noBlocks_Uniforms);

	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		noBlocks_Uniforms.worldMatrix = glm::translate(perspectiveMatrix, camMovement);

        for(unsigned int d = 0; d < MPerComponent.size(); d++){
            glBindVertexArray(MPerComponent.at(d).VertexArray);
			glBindTextureUnit(0, textureOrder[d]);
            if(MPerComponent.at(d).renderParams[ShaderCtrlBit::drawable] == 0)
                glDrawElements(GL_TRIANGLES, MPerComponent.at(d).modelIndices.size(), GL_UNSIGNED_INT, 0);
		}
        glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resources -- -- -- */

    glfwTerminate();
    return 0;
}
