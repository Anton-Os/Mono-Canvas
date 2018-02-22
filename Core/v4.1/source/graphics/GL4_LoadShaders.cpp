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
    } else printf("%s compiled successfuly \n", filePath_arg.c_str());

    delete[] shader_source;
    return shader;
}

GLuint compileShader(const std::string& filePath_arg, _GL4_Shader_Stage::Pick* stage_arg){
    GLuint shader;
    size_t filePath_length = filePath_arg.size();
    std::string extension = filePath_arg.substr(filePath_length - 4, filePath_length);

    if(extension == "vert"){
        shader = glCreateShader(GL_VERTEX_SHADER);
        *stage_arg = _GL4_Shader_Stage::vert;
    }
    else if(extension == "frag"){
        shader = glCreateShader(GL_FRAGMENT_SHADER);
        *stage_arg = _GL4_Shader_Stage::frag;
    } else logError(__FILE__, __LINE__, error_glslExtension);

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
    } else printf("%s compiled successfuly \n", filePath_arg.c_str());

    delete[] shader_source;
    return shader;
}