
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
// glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(4.0f), 0.9f, 0.1f, 1000.0f);

/* void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
		noBlocks_Uniforms.defaultColor = { 0.5f, 0.5f, 0.5f, 0.4f };
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS){
		std::cout << "Hot" << std::endl;
		noBlocks_Uniforms.defaultColor = { 0.9607f, 0.6862f, 0.0f, 0.4f };
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS){
		std::cout << "Cool" << std::endl;
		noBlocks_Uniforms.defaultColor = {0.2588f, 0.5254f, 0.9568f, 0.4f};
	}
	if(key == GLFW_KEY_4 && action == GLFW_PRESS){
		std::cout << "Neutral" << std::endl;
		noBlocks_Uniforms.defaultColor = {0.3372f, 0.749f, 0.4862f, 0.4f};
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
		rotateAngleX -= 1.0f;
		noBlocks_Uniforms.localMatrix = glm::rotate(noBlocks_Uniforms.localMatrix, glm::radians(rotateAngleX), glm::vec3(1.0f, 0.0, 0.0));
	}
} */

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W && action == GLFW_PRESS) Key::W = true;
	if (key == GLFW_KEY_A && action == GLFW_PRESS) Key::A = true;
	if (key == GLFW_KEY_S && action == GLFW_PRESS) Key::S = true;
	if (key == GLFW_KEY_D && action == GLFW_PRESS) Key::D = true;
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) Key::Q = true;
	if (key == GLFW_KEY_E && action == GLFW_PRESS) Key::E = true;
	if (key == GLFW_KEY_H && action == GLFW_PRESS) Key::U = true;
	if (key == GLFW_KEY_U && action == GLFW_PRESS) Key::H = true;
	if (key == GLFW_KEY_J && action == GLFW_PRESS) Key::J = true;
	if (key == GLFW_KEY_I && action == GLFW_PRESS) Key::I = true;
	if (key == GLFW_KEY_K && action == GLFW_PRESS) Key::K = true;
	if (key == GLFW_KEY_O && action == GLFW_PRESS) Key::O = true;
	if (key == GLFW_KEY_L && action == GLFW_PRESS) Key::L = true;
	if (key == GLFW_KEY_P && action == GLFW_PRESS) Key::P = true;

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) 
	noBlocks_Uniforms.defaultColor = { 0.5f, 0.5f, 0.5f, 0.7f };
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	noBlocks_Uniforms.defaultColor = { 0.9607f, 0.6862f, 0.0f, 0.7f };
	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	noBlocks_Uniforms.defaultColor = { 0.2588f, 0.5254f, 0.9568f, 0.7f };
	if(key == GLFW_KEY_4 && action == GLFW_PRESS)
	noBlocks_Uniforms.defaultColor = { 0.3372f, 0.749f, 0.4862f, 0.7f }; 

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) Key::W = false;
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) Key::A = false;
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) Key::S = false;
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) Key::D = false;
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE) Key::Q = false;
	if (key == GLFW_KEY_E && action == GLFW_RELEASE) Key::E = false;
	if (key == GLFW_KEY_H && action == GLFW_RELEASE) Key::H = false;
	if (key == GLFW_KEY_U && action == GLFW_RELEASE) Key::U = false;
	if (key == GLFW_KEY_J && action == GLFW_RELEASE) Key::J = false;
	if (key == GLFW_KEY_I && action == GLFW_RELEASE) Key::I = false;
	if (key == GLFW_KEY_K && action == GLFW_RELEASE) Key::O = false;
	if (key == GLFW_KEY_O && action == GLFW_RELEASE) Key::K = false;
	if (key == GLFW_KEY_L && action == GLFW_RELEASE) Key::L = false;
	if (key == GLFW_KEY_P && action == GLFW_RELEASE) Key::P = false;

	if(Key::W){	camMovement.z += 3.0f; }
	if(Key::A){ camMovement.x += 1.0f; }
	if(Key::S){ camMovement.z -= 3.0f; }
	if(Key::D){ camMovement.x -= 1.0f; }
	if(Key::Q){ camMovement.y -= 1.0f; }
	if(Key::E){ camMovement.y += 1.0f; }
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

	std::string noBlocks_vert = parentDir + "\\shaders\\NoBlocks.vert";
    std::string noBlocks_frag = parentDir + "\\shaders\\NoBlocks.frag";
    GLuint noBlocks_glsl = compileShaders(noBlocks_vert, noBlocks_frag);

	std::string brushedSteel_filePath = parentDir + "\\..\\..\\data\\BrushedSteel.ktx";
	GLuint brushedSteel = createTexture(brushedSteel_filePath.c_str());
	std::string scratchedSteel_filePath = parentDir + "\\..\\..\\data\\ScratchedSteel.ktx";
	GLuint scratchedSteel = createTexture(scratchedSteel_filePath.c_str());
	std::string limeStone_filePath = parentDir + "\\..\\..\\data\\LimeStone.ktx";
	GLuint limeStone = createTexture(limeStone_filePath.c_str());
	std::string sevenGrass_filePath = parentDir + "\\..\\..\\data\\SevenGrass.ktx";
	GLuint sevenGrass = createTexture(sevenGrass_filePath.c_str());
	std::string treeBark_filePath = parentDir + "\\..\\..\\data\\TreeBark.ktx";
	GLuint treeBark = createTexture(treeBark_filePath.c_str());
	std::string youngLeaves_filePath = parentDir + "\\..\\..\\data\\YoungLeaves.ktx";
	GLuint youngLeaves = createTexture(youngLeaves_filePath.c_str());
	std::string lightWood_filePath = parentDir + "\\..\\..\\data\\LightWood.ktx";
	GLuint lightWood = createTexture(lightWood_filePath.c_str());
	std::string medWood_filePath = parentDir + "\\..\\..\\data\\MedWood.ktx";
	GLuint medWood = createTexture(medWood_filePath.c_str());
	std::string woodPlanks_filePath = parentDir + "\\..\\..\\data\\WoodPlanks.ktx";
	GLuint woodPlanks = createTexture(woodPlanks_filePath.c_str());

	std::array<GLuint, 8> textureOrder = 
	{ 0, 0, youngLeaves, treeBark, sevenGrass, medWood, limeStone, lightWood };

    std::vector<ModelComposite> MPerComponent;
	std::string Nut_filePath = parentDir + "\\..\\..\\data\\nut.fbx";
    std::string LowPolyMill_filePath = parentDir + "\\..\\..\\data\\LowPolyMill.fbx";

    assimpImportCPP(LowPolyMill_filePath, &MPerComponent);

	glUseProgram(noBlocks_glsl);

	noBlocks_Uniforms.worldMatrix = perspectiveMatrix;
	noBlocks_Uniforms.defaultColor = { 0.9607f, 0.6862f, 0.0f, 0.8f };
    noBlocks_Uniforms.surfaceRenderMode = 3;

	NoBlocks noBlocksUtil(noBlocks_glsl);
    noBlocksUtil.setUniforms(&noBlocks_Uniforms);

	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// noBlocksUtil.localMatrix(&noBlocks_Uniforms);
		noBlocks_Uniforms.worldMatrix = glm::translate(perspectiveMatrix, camMovement);
		noBlocksUtil.worldMatrix(&noBlocks_Uniforms);
		noBlocksUtil.defaultColor(&noBlocks_Uniforms);

        for(unsigned int d = 0; d < MPerComponent.size(); d++){
            glBindVertexArray(MPerComponent.at(d).VertexArray);
			// glBindTextureUnit(0, MPerComponent.at(d).currentTexture);
			glBindTextureUnit(0, textureOrder[d]);
            if(MPerComponent.at(d).renderParams[ShaderCtrlBit::drawable] == 0);
                glDrawElements(GL_TRIANGLES, MPerComponent.at(d).modelIndices.size(), GL_UNSIGNED_INT, 0);
		}
        glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

    /* -- -- -- Deallocation and deletion of resources -- -- -- */

    glfwTerminate();
    return 0;
}
