#ifndef LOADERS_H
    #include "Loaders.h"
    #define LOADERS_H
#endif

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
    const GLchar* vertex_shader_source = readFile(vertex_shader_absolute_path.c_str());
    const GLchar* fragment_shader_source = readFile(fragment_shader_absolute_path.c_str());
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