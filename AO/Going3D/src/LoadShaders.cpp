#include "Common.h"

#include <GL/glew.h>

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
