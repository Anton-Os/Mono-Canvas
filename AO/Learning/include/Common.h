
// From LoadShaders.cpp

GLchar* readShaderFile(const char* nameOfShader);
GLuint compileShaders(const std::string &rootpath, const char* vertexShaderBaseName, const char* fragmentShaderBaseName);

// From LoadTextures.cpp

GLuint createTexture(const char* filePath);