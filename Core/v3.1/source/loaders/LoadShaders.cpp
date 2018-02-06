#include "graphics/GL4_LoadShaders.hpp"

static char error_glslExtension[] = "Unknown glsl file extension";
static char error_shaderCompile[] = "Shader failed to compile";

GLuint compileShader(const std::string& filePath_arg){
    GLuint shader;
    size_t filePath_length = filePath_arg.size();
    std::string extension = filePath_arg.substr(filePath_length - 4, filePath_length);

    if(extension == "vert") shader = glCreateShader(GL_VERTEX_SHADER);
    else if(extension == "frag") shader = glCreateShader(GL_FRAGMENT_SHADER);
    else logError(__FILE__, __LINE__, error_glslExtension);

    const GLchar* shader_source = readFile(filePath_arg.c_str());
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
    
    GLint logState;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &logState);
    if(!logState){
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        puts(infoLog);
        logError(__FILE__, __LINE__, error_shaderCompile);
    } else printf("%s compiled successfuly", filePath_arg.c_str());

    delete[] shader_source;
    return shader;
}

GLuint compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
    GLuint vertex_shader, fragment_shader, shader_program;
    GLint logState;
    GLchar infoLog[512];

    const GLchar* vertex_shader_source = readFile(vertexShaderFilePath.c_str());
    const GLchar* fragment_shader_source = readFile(fragmentShaderFilePath.c_str());

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