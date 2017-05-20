#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <cmath>
#include <ctime>
#include <cstdio>
// #include <locale>

#include <windows.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>


// glEnable(GL_PRIMITIVE_RESTART);

void antialias(){
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

void sendXYZW(const GLfloat data[], GLuint VBOid, GLuint currentAttrib, std::size_t nPoints){

    GLsizeiptr size = nPoints * sizeof(GLfloat);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(currentAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(currentAttrib);
}

void sendRGBA(const GLubyte data[], GLuint VBOid, GLuint currentAttrib, std::size_t nPoints){

    GLsizeiptr size = nPoints * sizeof(GLubyte);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(currentAttrib, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glEnableVertexAttribArray(currentAttrib);
}

void initIndices(GLuint VBOid){

    const GLubyte indices1[] = {
            11, 5, 6,
            1, 8, 10,
            2, 4, 3
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
}

void drawElements(){
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBOs[6];
    glGenBuffers(6, VBOs);

    GLuint startingIndex = 0;
    // GLuint zeroOffset = 0;
    GLuint first = 0;
    GLfloat zDef = 0.5f;
    GLfloat wDef = 1.0f;
    GLubyte alpha = 255;

    const GLfloat coord[] = {
        0.5f, 0.5f, zDef, wDef,
        -0.5f, -0.5f, zDef, wDef,
        0.5f, -0.5f, zDef, wDef
    };

    const GLfloat coord2[] = {
        0.9f, 0.9f, zDef, wDef,
        0.9f, 0.9f, zDef, wDef,
        0, 0, zDef, wDef,
        -0.1f, -0.9f, zDef, wDef,
        0.8f, -0.8f, zDef, wDef,
        0.7f, -0.4f, zDef, wDef
    };

    /* const GLfloat coord3[] = {
        0.5f, 0.5f, zDef, wDef,
        -0.5f, -0.5f, zDef, wDef,
        0.1f, -0.1f, zDef, wDef,
        0.9f, 0.8f, zDef, wDef,
        0.7f, 0.8f, zDef, wDef,
        0.3f, 0.3f, zDef, wDef,
        0.1f, -0.4f, zDef, wDef,
        -0.5f, 0.4f, zDef, wDef,
        -0.5f, -0.7f, zDef, wDef,
    }; */

    const GLfloat coord3[] = {
        0.5f, 0.4f, zDef, wDef,
        0.4f, -0.5f, zDef, wDef,
        -0.4f, -0.5f, zDef, wDef,
        -0.99f, -0.6f, zDef, wDef,
        -0.99f, -0.99f, zDef, wDef,
        -0.6f, -0.99f, zDef, wDef,
        0.4f, 0.3f, zDef, wDef,
        0.7f, -0.3f, zDef, wDef,
        -0.3f, 0.7f, zDef, wDef
    };

    const GLubyte colors[] = {
        60, 119, 214, alpha,
        60, 119, 214, alpha,
        129, 173, 244, alpha,
    };

    /* const GLubyte colors2[] = {
        255, 82, 105, alpha,
        255, 82, 105, alpha,
        178, 33, 53, alpha,
        255, 82, 105, alpha,
        255, 82, 105, alpha,
        158, 13, 33, alpha
    }; */

    const GLubyte colors2[] = {
        63, 116, 191, 255,
        63, 116, 191, 255,
        44, 150, 220, 255,
        222, 95, 88, 255,
        222, 95, 88, 255,
        229, 136, 102, 255
    };

    const GLubyte colors3[] = {
        60, 119, 214, alpha,
        60, 119, 214, alpha,
        60, 119, 214, alpha,
        74, 247, 161, alpha,
        74, 247, 161, alpha,
        74, 247, 161, alpha,
        255, 82, 105, alpha,
        255, 82, 105, alpha,
        255, 82, 105, alpha
    };

    sendXYZW(coord, VBOs[startingIndex], startingIndex, sizeof(coord) / sizeof(GLfloat));
    startingIndex++; // 1
    sendRGBA(colors, VBOs[startingIndex], startingIndex, sizeof(colors) / sizeof(GLubyte));
    startingIndex++; // 2
    sendXYZW(coord2, VBOs[startingIndex], startingIndex, sizeof(coord2) / sizeof(GLfloat));
    startingIndex++; // 3
    sendRGBA(colors2, VBOs[startingIndex], startingIndex, sizeof(colors2) / sizeof(GLubyte));
    startingIndex++; // 4
    sendXYZW(coord3, VBOs[startingIndex], startingIndex, sizeof(coord3) / sizeof(GLfloat));
    startingIndex++; // 5
    sendRGBA(colors3, VBOs[startingIndex], startingIndex, sizeof(coord3) / sizeof(GLubyte));
    startingIndex++; // 6

    glClearColor(240.0f / 255.0f, 232.0f / 255.0f, 213.0f / 255.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glFlush();

    return;
}

/* void drawElements2(){
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBOs[5];
    glGenBuffers(5, VBOs);

    GLuint startingIndex = 0;
    // GLuint zeroOffset = 0;
    GLuint first = 0;
    GLfloat zDef = 0.5f;
    GLfloat wDef = 1.0f;
    GLfloat alpha = 255;

    sendXYZW(coord, VBOs[startingIndex], startingIndex, sizeof(coord) / sizeof(GLfloat));
    startingIndex++; // 1
    sendRGBA(colors, VBOs[startingIndex], startingIndex, sizeof(colors) / sizeof(GLubyte));
    startingIndex++; // 2
    sendXYZW(coord2, VBOs[startingIndex], startingIndex, sizeof(coord2) / sizeof(GLfloat));
    startingIndex++; // 3
    sendRGBA(colors2, VBOs[startingIndex], startingIndex, sizeof(colors2) / sizeof(GLubyte));
    startingIndex++; // 4

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glFlush();

} */

GLuint freeglutConfig(const char* nameOfWindow){
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(512, 512);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(nameOfWindow);
    return 0;
}

void checkGLEW2(){
    GLenum err = glewInit();
    if (GLEW_OK != err){
        // Problem: glewInit failed, something is seriously wrong.
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

const std::string getParentDirectory(const char* path) {
    const char* ptr = path + strlen(path);
    while (ptr != path && nullptr == strchr("\\/", *(--ptr)));
    std::size_t len = ptr - path;
    std::string result(path, len);
    std::cout << "Parent dir: " << result << std::endl;
    return result;
}

 

GLuint compileShaders(const std::string& rootPath){
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint shader_program;
    const char* vertex_shader_base_name = "B1.vert";
    const char* fragment_shader_base_name = "B1.frag";
    std::string vertex_shader_absolute_path((rootPath.length() > 0) ?
                                            rootPath + "\\" + vertex_shader_base_name :
                                            std::string(vertex_shader_base_name));
    std::string fragment_shader_absolute_path((rootPath.length() > 0) ?
                                              rootPath + "\\" + fragment_shader_base_name :
                                              std::string(fragment_shader_base_name));
    const GLchar* vertex_shader_source = readShaderFile(vertex_shader_absolute_path.c_str());
    const GLchar* fragment_shader_source = readShaderFile(fragment_shader_absolute_path.c_str());
    vertex_shader_absolute_path;
    fragment_shader_absolute_path;

    std::cout << std::endl << vertex_shader_source << std::endl;
    std::cout << std::endl << fragment_shader_source << std::endl;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    delete[] vertex_shader_source;

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    delete[] fragment_shader_source;

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

/* int main(int argc, char ** argv){
    std::string parentDir(getParentDirectory(argv[0]));
    glutInit(&argc, argv);
    freeglutConfig("OpenGL Dimentions");
    checkGLEW2();
    GLuint shaderProgram = compileShaders(parentDir);
    glUseProgram(shaderProgram);
    antialias();
    glutDisplayFunc(drawElements);
    glutMainLoop();
} */

int main(int argc, char** argv){

    int w, h;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "MonoCanvas", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    return 0;
}
