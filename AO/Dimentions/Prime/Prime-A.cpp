#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <string>
#include <array>
#include <cmath>
#include <ctime>
#include <cstddef>
#include <cstdio>
#include <cerrno>

#include <GL/glew.h>
#include <GL/freeglut.h>

// glEnable(GL_PRIMITIVE_RESTART);

void antialias(){
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

void init() {
    GLuint VAO;
    GLuint VBOids[3];
    /* GLuint VBOcoord;
    GLuint VBOcolor;
    GLuint VBOindices; */

    GLuint vPosition = 0;
    GLuint vPosition1 = 1;
    GLuint vPosition2 = 2;
    GLuint fColor = 3;
    GLfloat zDef = 0.5f;
    GLfloat wDef = 1.0f;
    GLubyte alpha = 255;
    GLuint arrayBufferOffset = 0;

    const GLfloat coordinates[] = {
            0.5f, 0.5f, zDef, wDef,
            -0.5f, -0.5f, zDef, wDef,
            0.7f, -0.7f, zDef, wDef,
            -0.7f, 0.7f, zDef, wDef,
            -0.95f, -0.75f, zDef, wDef,
            -0.75f, -0.95f, zDef, wDef,
            -0.55f, -0.55f, zDef, wDef
    };

    const GLfloat coordinates1[] = {
            -0.7f, 0.7f, zDef, wDef, // 0
            -0.7f, -0.7f, zDef, wDef, // 1
            0.7f, 0.7f, zDef, wDef, // 2
            0.7f, -0.7f, zDef, wDef // 3
    };

    const GLfloat coordinates2[] = {
            -0.3f, 0.3f, zDef, wDef, // 4
            -0.3f, -0.3f, zDef, wDef, // 5
            0.3f, 0.3f, zDef, wDef, // 6
            0.3f, -0.3f, zDef, wDef // 7
    };

    const GLfloat coordinates3[] = {
            -0.5f, 0.5f, zDef, wDef, // 8
            -0.5f, -0.5f, zDef, wDef, // 9
            0.5f, 0.5f, zDef, wDef, // 10
            0.5f, -0.5f, zDef, wDef // 11
    };

    const GLubyte colors[] = {
            60, 119, 214, alpha,
            60, 119, 214, alpha,
            74, 247, 161, alpha,
            74, 247, 161, alpha,
            255, 82, 105, alpha,
            255, 82, 105, alpha,
            255, 82, 105, alpha
    };

    const GLubyte colors1[] = {
            60, 119, 214, alpha,
            60, 119, 214, alpha,
            60, 119, 214, alpha,
            60, 119, 214, alpha,
            74, 247, 161, alpha,
            74, 247, 161, alpha,
            74, 247, 161, alpha,
            74, 247, 161, alpha,
            255, 82, 105, alpha,
            255, 82, 105, alpha,
            255, 82, 105, alpha,
            255, 82, 105, alpha
    };

    const GLubyte indices[] = {
            0, 1, 2,
            0, 1, 3,
            4, 5, 6
    };

    const GLubyte indices1[] = {
            11, 5, 6,
            1, 8, 10,
            2, 4, 3
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    /* glGenBuffers(1, &VBOcoord);
    glBindBuffer(GL_ARRAY_BUFFER, VBOcoord); */
    glGenBuffers(3, VBOids);
    glBindBuffer(GL_ARRAY_BUFFER, VBOids[0]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates1) + sizeof(coordinates2) + sizeof(coordinates3), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, arrayBufferOffset, sizeof(coordinates1), coordinates1);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition);
    arrayBufferOffset += sizeof(coordinates1);

    glBufferSubData(GL_ARRAY_BUFFER, arrayBufferOffset, sizeof(coordinates2), coordinates2);
    glVertexAttribPointer(vPosition1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition1);
    arrayBufferOffset += sizeof(coordinates2);

    glBufferSubData(GL_ARRAY_BUFFER, arrayBufferOffset, sizeof(coordinates3), coordinates3);
    glVertexAttribPointer(vPosition2, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition2);
    // arrayBufferOffset += sizeof(coordinates3);

    /* glGenBuffers(1, &VBOcolor);
    glBindBuffer(GL_ARRAY_BUFFER, VBOcolor); */
    glBindBuffer(GL_ARRAY_BUFFER, VBOids[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
    glVertexAttribPointer(fColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glEnableVertexAttribArray(fColor);

    /* glGenBuffers(1, &VBOindices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindices); */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOids[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
}

void init2(){
    GLuint VAO;
    GLuint VBOids[3];

    GLuint vPosition = 0;
    GLuint vPosition1 = 1;
    GLuint vPosition2 = 2;
    GLuint fColor = 3;
    GLfloat zDef = 0.5f;
    GLfloat wDef = 1.0f;
    GLubyte alpha = 255;
    GLuint arrayBufferOffset = 0;

    const GLfloat coordinates1[] = {
            -0.7f, 0.7f, zDef, wDef, // 0
            -0.7f, -0.7f, zDef, wDef, // 1
            0.7f, 0.7f, zDef, wDef, // 2
            0.7f, -0.7f, zDef, wDef // 3
    };

    const GLfloat coordinates2[] = {
            -0.3f, 0.3f, zDef, wDef, // 4
            -0.3f, -0.3f, zDef, wDef, // 5
            0.3f, 0.3f, zDef, wDef, // 6
            0.3f, -0.3f, zDef, wDef // 7
    };

    const GLfloat coordinates3[] = {
            -0.5f, 0.5f, zDef, wDef, // 8
            -0.5f, -0.5f, zDef, wDef, // 9
            0.5f, 0.5f, zDef, wDef, // 10
            0.5f, -0.5f, zDef, wDef // 11
    };

    const GLubyte colors1[] = {
            60, 119, 214, alpha,
            60, 119, 214, alpha,
            60, 119, 214, alpha,
            60, 119, 214, alpha,
            74, 247, 161, alpha,
            74, 247, 161, alpha,
            74, 247, 161, alpha,
            74, 247, 161, alpha,
            255, 82, 105, alpha,
            255, 82, 105, alpha,
            255, 82, 105, alpha,
            255, 82, 105, alpha
    };

    const GLubyte indices1[] = {
            11, 5, 6,
            1, 8, 10,
            2, 4, 3
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(3, VBOids);
    glBindBuffer(GL_ARRAY_BUFFER, VBOids[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates1) + sizeof(coordinates2) + sizeof(coordinates3), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, arrayBufferOffset, sizeof(coordinates1), coordinates1);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition);
    arrayBufferOffset += sizeof(coordinates1);

    glBufferSubData(GL_ARRAY_BUFFER, arrayBufferOffset, sizeof(coordinates2), coordinates2);
    glVertexAttribPointer(vPosition1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition1);
    arrayBufferOffset += sizeof(coordinates2);

    glBufferSubData(GL_ARRAY_BUFFER, arrayBufferOffset, sizeof(coordinates3), coordinates3);
    glVertexAttribPointer(vPosition2, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition2);
    // arrayBufferOffset += sizeof(coordinates3);

    glBindBuffer(GL_ARRAY_BUFFER, VBOids[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
    glVertexAttribPointer(fColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glEnableVertexAttribArray(fColor);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOids[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
}

/* void init_Points() {
    GLuint VAO;
    GLuint VBOcoord;
    GLuint VBOindices;

    GLfloat z1 = 0.5f;
    GLfloat w1 = 1.0f;

    const GLfloat coordinates[] = {
        0.5f, 0.5f, z1, w1,
        -0.5f, -0.5f, z1, w1,
        0.7f, -0.7f, z1, w1,
        -0.7f, 0.7f, z1, w1,
        -0.95f, -0.75f, z1, w1,
        -0.75f, -0.95f, z1, w1,
        -0.55f, -0.55f, z1, w1
    };

    const GLubyte indices[] = {
        0, 1, 2,
        0, 1, 3,
        4, 5, 6
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBOcoord);
    glBindBuffer(GL_ARRAY_BUFFER, VBOcoord);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &VBOindices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
} */

/* void init_Colors(GLubyte alphaValue) {
    GLuint VAO2;
    GLuint VBOcolor;

    GLubyte alpha = alphaValue;

    GLubyte red1 = 60;
    GLubyte red2 = 74;
    GLubyte red3 = 255;
    GLubyte green1 = 119;
    GLubyte green2 = 247;
    GLubyte green3 = 82;
    GLubyte blue1 = 214;
    GLubyte blue2 = 161;
    GLubyte blue3 = 105;

    GLubyte colors[] = {
            red1, green1, blue1, alpha,
            red1, green1, blue1, alpha,
            red2, green2, blue2, alpha,
            red2, green2, blue2, alpha,
            red3, green3, blue3, alpha,
            red3, green3, blue3, alpha,
            red3, green3, blue3, alpha
    };

    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    glGenBuffers(1, &VBOcolor);
    glBindBuffer(GL_ARRAY_BUFFER, VBOcolor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glEnableVertexAttribArray(1);
} */

GLuint initXYZW(GLuint VBOid, GLuint startingAttrib){

    // Phase 1

    GLuint currentAttrib = startingAttrib;

    GLfloat zDef = 0.5f;
    GLfloat wDef = 1.0f;

    GLuint arrayBufferOffset = 0;

    static const GLfloat coordinates1[] = {
            -0.7f, 0.7f, zDef + 0.1f, wDef, // 0
            -0.7f, -0.7f, zDef + 0.1f, wDef, // 1
            0.7f, 0.7f, zDef + 0.1f, wDef, // 2
            0.7f, -0.7f, zDef + 0.1f, wDef // 3
    };

    static const GLfloat coordinates2[] = {
            -0.3f, 0.3f, zDef, wDef, // 4
            -0.3f, -0.3f, zDef, wDef, // 5
            0.3f, 0.3f, zDef, wDef, // 6
            0.3f, -0.3f, zDef, wDef // 7
    };

    static const GLfloat coordinates3[] = {
            -0.5f, 0.5f, zDef - 0.1f, wDef, // 8
            -0.5f, -0.5f, zDef - 0.1f, wDef, // 9
            0.5f, 0.5f, zDef - 0.1f, wDef, // 10
            0.5f, -0.5f, zDef - 0.1f, wDef // 11
    };

    // Phase 2

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates1) + sizeof(coordinates2) + sizeof(coordinates3), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, arrayBufferOffset, sizeof(coordinates1), coordinates1);
    glVertexAttribPointer(currentAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(currentAttrib);
    arrayBufferOffset += sizeof(coordinates1);
    currentAttrib++; // 0

    glBufferSubData(GL_ARRAY_BUFFER, arrayBufferOffset, sizeof(coordinates2), coordinates2);
    glVertexAttribPointer(currentAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(currentAttrib);
    arrayBufferOffset += sizeof(coordinates2);
    currentAttrib++; // 1

    glBufferSubData(GL_ARRAY_BUFFER, arrayBufferOffset, sizeof(coordinates3), coordinates3);
    glVertexAttribPointer(currentAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(currentAttrib);
    currentAttrib++; // 2
    // arrayBufferOffset += sizeof(coordinates3);

    return currentAttrib;
}

/* GLuint initXYZW2(GLuint VBOid, GLuint startingAttrib){
	GLuint currentAttrib = startingAttrib;

	struct vPositionAll {

		GLfloat zDef = 0.5f;
		GLfloat wDef = 1.0f;

		const GLfloat coordinates1[16] = {
			-0.7f, 0.7f, zDef + 0.1f, wDef, // 0
			-0.7f, -0.7f, zDef + 0.1f, wDef, // 1
			0.7f, 0.7f, zDef + 0.1f, wDef, // 2
			0.7f, -0.7f, zDef + 0.1f, wDef // 3
		};

		const GLfloat coordinates2[16] = {
			-0.3f, 0.3f, zDef, wDef, // 4
			-0.3f, -0.3f, zDef, wDef, // 5
			0.3f, 0.3f, zDef, wDef, // 6
			0.3f, -0.3f, zDef, wDef // 7
		};

		const GLfloat coordinates3[16] = {
			-0.5f, 0.5f, zDef - 0.1f, wDef, // 8
			-0.5f, -0.5f, zDef - 0.1f, wDef, // 9
			0.5f, 0.5f, zDef - 0.1f, wDef, // 10
			0.5f, -0.5f, zDef - 0.1f, wDef // 11
		};
	};
} */

GLuint initRGBA(GLuint VBOid, GLuint startingAttrib) {

    GLuint currentAttrib = startingAttrib;
    GLubyte alpha = 255;

    const GLubyte colors1[] = {
            60, 119, 214, alpha,
            60, 119, 214, alpha,
            60, 119, 214, alpha,
            60, 119, 214, alpha,
            74, 247, 161, alpha,
            74, 247, 161, alpha,
            74, 247, 161, alpha,
            74, 247, 161, alpha,
            255, 82, 105, alpha,
            255, 82, 105, alpha,
            255, 82, 105, alpha,
            255, 82, 105, alpha
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);
    glVertexAttribPointer(currentAttrib, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glEnableVertexAttribArray(currentAttrib);
    currentAttrib++; // 3

    return currentAttrib;
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

void initPlus(){
    return;
}

void drawElements(){
    /* glClearColor(239.0f / 255.0f, 227.0f / 255.0f, 214.0f / 255.0f, 1.0f);
    glClearColor(225.0f / 255.0f, 229.0f / 255.0f, 204.0f / 255.0f, 1.0f); */
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_BYTE, 0);
    // glDrawElements(GL_TRIANGLE_STRIP, 9, GL_UNSIGNED_BYTE, 0);
    glFlush();
}

void drawElements2(){

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBOids[3];
    glGenBuffers(3, VBOids);

    GLuint shaderIndex1 = initXYZW(VBOids[0], 0);
    initRGBA(VBOids[1], shaderIndex1);
    initIndices(VBOids[2]);
    for (GLuint iterations = 0; iterations < 60; iterations++){
        // initPlus();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_BYTE, 0);
        glFlush();
        // glutSwapBuffers();
    }
}

/* void timePlay(){

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

GLuint compileShaders(const std::string& rootPath){
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint shader_program;
    const char* vertex_shader_base_name = "A1.vert";
    const char* fragment_shader_base_name = "A1.frag";
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

int main(int argc, char ** argv){
    std::string parentDir(getParentDirectory(argv[0]));
    glutInit(&argc, argv);
    freeglutConfig("OpenGL Dimentions");
    checkGLEW2();
    GLuint shaderProgram = compileShaders(parentDir);
    glUseProgram(shaderProgram);
    antialias();
    // init2();
    glutDisplayFunc(drawElements2);
    glutMainLoop();
}
