#ifndef LOADSHADER
#define LOADSHADER

// Reads the parent directory of file provided to <path>
// const std::string getParentDirectory(const char* path);

// Reads data within file <nameOfShader> with a c-style filestream and returns the text as GLchar*
// Private to LoadShaders-D.cpp but can be used to extract contents of any file
GLchar* readShaderFile(const char* nameOfShader);

// Populates, compiles, and links shader files to a shader program using vertex and fragment shader
GLuint compileShaders(const std::string &rootpath, const char* vertexShaderBaseName, const char* fragmentShaderBaseName);

/* EXAMPLE

    #include LoadShaders-D.h

    int main(int argc, char** argv){
        std::string parentdir(getParentDirectory(argv[0]));
        GLuint shaderProgram = compileShaders(parentDir);
        glUseProgram(shaderProgram);
        return 0;
    }

*/

#endif