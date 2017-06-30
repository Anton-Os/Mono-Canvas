#include "Common.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SimpleDiffuse {

public:
	GLuint shaderProgram;
	glm::vec3 cameraPos;
	glm::vec3 modelPos;

	glm::mat4 Projection(1);
	glm::mat4 View(1);
	glm::mat4 Model(1);

	GLfloat ambientLightStrength;
	GLfloat worldLightColor[3];
	GLfloat lightSourcePos[3];

	SimpleDiffuse(GLuint shaderProgramID, glm::vec3 currentCameraPos, glm::vec3 currentModelPos) {
		shaderProgram = shaderProgramID;
		cameraPos = currentCameraPos;
		modelPos = currentModelPos;

		Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 200.f);
		View = glm::lookAt(cameraPos, cube1_Origin, glm::vec3(0.0, 1.0f, 0.0));
		Model = glm::translate(glm::mat4(1), modelPos);

		ambientLightStrength = 0.8f;
		worldLightColor = { 1.0f, 1.0f, 1.0f };
		lightSourcePos = { 0, 10.0f, 0 };
	}

	void updateVert() {
		GLint Projection_loc = glGetUniformLocation(shaderProgram, "Projection");
	}

	void updateFrag() {
	
	}

	void updateAll() {
		updateVert();
		updateFrag();
	}
};