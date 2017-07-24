#include "Common.h"

#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Handles operations related to GLSL Shaders */

GLchar* readShaderFile(const char* nameOfShader){
    FILE* shaderFile = fopen(nameOfShader, "r");
    if (nullptr == shaderFile) {
        std::cerr << "Failed to open shader file: " << nameOfShader << std::endl;
        return nullptr;
    }
    fseek(shaderFile, 0, SEEK_END);
    int shaderLength = ftell(shaderFile);
    fseek(shaderFile, 0, SEEK_SET);

    GLchar* shaderSource = new GLchar[shaderLength + 1];
    // second argument specifies size in bytes
    std::size_t n = fread(shaderSource, 1, shaderLength, shaderFile);
    if (n <= 0) {
        std::cerr << "Failed to read shader file (got " << n
                  << " bytes, expected " << shaderLength << " bytes)" << std::endl;
        return nullptr;
    }
    fclose(shaderFile);
    shaderSource[n] = '\0';

    // cast to constant NOW because earlier fread cannot use shaderSource
    return shaderSource;
}

GLuint compileShaders(const std::string& rootPath, const char* vertexShaderBaseName, const char* fragmentShaderBaseName){
    GLuint vertex_shader, fragment_shader, shader_program;
    GLint logState;
    GLchar infoLog[512];
    std::string vertex_shader_absolute_path((rootPath.length() > 0) ?
                                            rootPath + "\\" + vertexShaderBaseName :
                                            std::string(vertexShaderBaseName));
    std::string fragment_shader_absolute_path((rootPath.length() > 0) ?
                                              rootPath + "\\" + fragmentShaderBaseName :
                                              std::string(fragmentShaderBaseName));
    const GLchar* vertex_shader_source = readShaderFile(vertex_shader_absolute_path.c_str());
    const GLchar* fragment_shader_source = readShaderFile(fragment_shader_absolute_path.c_str());
    vertex_shader_absolute_path;
    fragment_shader_absolute_path;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &logState);
    if(!logState){
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cerr << vertexShaderBaseName << " failed to compile...\n\n" 
                  << infoLog << std::endl;
        return 1;
    } else {
        std::cout << vertexShaderBaseName << " compiled successfuly...\n\n" << "VERTEX SHADER START >>\n\n" 
                  << vertex_shader_source << "\n << VERTEX SHADER END \n" << std::endl;
    }
    delete[] vertex_shader_source;

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &logState);
    if(!logState){
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cerr << fragmentShaderBaseName << " failed to compile...\n\n" 
                  << infoLog << std::endl;
        return 1;          
    } else {
        std::cout << fragmentShaderBaseName << " compiled successfuly...\n\n" << "FRAGMENT SHADER START >>\n\n" 
                  << fragment_shader_source << "\n << FRAGMENT SHADER END\n" << std::endl;
    }
    delete[] fragment_shader_source;

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &logState);
    if (!logState) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cerr << "Shader Program failed to link...\n\n" << infoLog << std::endl;
        return 1;
    } else {
        std::cout << "Shader program linked successfuly...\n" << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

GLuint compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
    GLuint vertex_shader, fragment_shader, shader_program;
    GLint logState;
    GLchar infoLog[512];

    const GLchar* vertex_shader_source = readShaderFile(vertexShaderFilePath.c_str());
    const GLchar* fragment_shader_source = readShaderFile(fragmentShaderFilePath.c_str());

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &logState);
    if(!logState){
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cerr << vertexShaderFilePath << " failed to compile...\n\n"
                  << infoLog << std::endl;
        return 1;
    } else {
        std::cout << vertexShaderFilePath << " compiled successfuly...\n\n" << "VERTEX SHADER START >>\n\n"
                  << vertex_shader_source << "\n << VERTEX SHADER END \n" << std::endl;
    }
    delete[] vertex_shader_source;

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &logState);
    if(!logState){
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cerr << fragmentShaderFilePath << " failed to compile...\n\n"
                  << infoLog << std::endl;
        return 1;
    } else {
        std::cout << fragmentShaderFilePath << " compiled successfuly...\n\n" << "FRAGMENT SHADER START >>\n\n"
                  << fragment_shader_source << "\n << FRAGMENT SHADER END\n" << std::endl;
    }
    delete[] fragment_shader_source;

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &logState);
    if (!logState) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cerr << "Shader Program failed to link...\n\n" << infoLog << std::endl;
        return 1;
    } else {
        std::cout << "Shader program linked successfuly...\n" << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

GLbyte* readShaderBytes(const char* nameOfShader){
    FILE* shaderFile = fopen(nameOfShader, "r");
    if (nullptr == shaderFile) {
        std::cerr << "Failed to open shader file: " << nameOfShader << std::endl;
        return nullptr;
    }
    fseek(shaderFile, 0, SEEK_END);
    int shaderLength = ftell(shaderFile);
    fseek(shaderFile, 0, SEEK_SET);

    GLchar* shaderSource = new GLchar[shaderLength + 1];
    // second argument specifies size in bytes
    std::size_t n = fread(shaderSource, 1, shaderLength, shaderFile);
    if (n <= 0) {
        std::cerr << "Failed to read shader file (got " << n
                  << " bytes, expected " << shaderLength << " bytes)" << std::endl;
        return nullptr;
    }
    fclose(shaderFile);
    shaderSource[n] = '\0';
    
    // cast to constant NOW because earlier fread cannot use shaderSource
    return (GLbyte*)shaderSource;
}

/* GLuint spirvProgram(const std::string& rootPath, const char* vertexBinaryName, const char* fragmentBinaryName){
    GLuint vertexBinary;
    GLuint fragmentBinary;

    std::string vertexBinaryAbsolutePath((rootPath.length() > 0) ?
                                          rootPath + "\\" + vertexBinaryName :
                                          std::string(vertexBinaryName));
    std::string fragmentBinaryAbsolutePath((rootPath.length() > 0) ?
                                            rootPath + "\\" + fragmentBinaryName :
                                            std::string(fragmentBinaryName));
    GLbyte* vertexBinarySource = readShaderBytes(vertexBinaryAbsolutePath.c_str());
    GLbyte* fragmentBinarySource = readShaderBytes(fragmentBinaryAbsolutePath.c_str());

    glShaderBinary(1, &vertexBinary, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB, sizeof(vertexBinarySource));
} */

void viewer3D_UniformBlocks(GLuint shaderProgID, ModelStatic* Model){
	GLuint vert_uniformBlockID = glGetUniformBlockIndex(shaderProgID, "vertexBlock");
	GLuint frag_uniformBlockID = glGetUniformBlockIndex(shaderProgID, "fragmentBlock");

	if(vert_uniformBlockID == GL_INVALID_INDEX) 
	std::cerr << "Uniform block 'vertexBlock' does not exist in vertex shader" << std::endl;

	if(frag_uniformBlockID == GL_INVALID_INDEX) 
	std::cerr << "Uniform block 'fragmentBlock' does not exist in fragment shader" << std::endl;

	struct vert_uniformData {
		glm::mat4 worldMatrix;
		glm::mat4 localMatrix;
	};

	struct frag_uniformData {
		GLfloat ambientLightStrength;
		GLuint surfaceRenderMode;
	};

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 200.f);
	glm::mat4 view = glm::mat4(1);

	glm::mat4 worldMatrix = projection * view;
	glm::mat4 localMatrix = glm::translate(glm::mat4(1), glm::vec3(0.0, 0.0, -5.0f));

    GLfloat ambientLightStrength = 1.0f;
	GLuint surfaceRenderMode;

    if(Model->renderParams[ShaderCtrlBit::color] == 1 && Model->renderParams[ShaderCtrlBit::texCoord] == 0){
		std::cout << "No vertex colors present, texture coordinates are" << std::endl;
		surfaceRenderMode = 0;
	} else {
		std::cerr << "We are in a caveman era" << std::endl;
		return;
	}

	vert_uniformData vertexBlock = {
		worldMatrix,
		localMatrix,
	};

	frag_uniformData fragmentBlock = {
		ambientLightStrength,
		surfaceRenderMode
	};

	glUniformBlockBinding(vert_uniformBlockID, shaderProgID, 0);
	glUniformBlockBinding(frag_uniformBlockID, shaderProgID, 1);

	GLuint UBO[2];
	glGenBuffers(2, UBO);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO[0]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(vertexBlock), &vertexBlock, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO[0]);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO[1]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(fragmentBlock), &fragmentBlock, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, UBO[1]);
}