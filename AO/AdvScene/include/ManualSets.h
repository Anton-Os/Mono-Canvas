#include <array>

#include <GL/glew.h>

GLfloat squarePos[] = {
    -1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};

GLuint squareIndices[] = {
    0, 1, 2, 3, 1, 2
};

struct ColorPalette4x3 {
    std::array<GLfloat, 3> color1;
    std::array<GLfloat, 3> color2;
    std::array<GLfloat, 3> color3;
    std::array<GLfloat, 3> color4;
};

ColorPalette4x3 warmPalette {
	{1.0f, 0.313f, 0.313f},
	{1.0f, 0.6f, 0.4f},
	{1.0f, 0.701f, 0.854f},
	{1.0f, 1.0f, 0.6f},
};

ColorPalette4x3 coolPalette {
	{0.219f, 0.447f, 0.819f},
	{0.243f, 0.4f, 0.76f},
	{0.466f, 0.615f, 0.819f},
	{0.76f, 0.913f, 0.96f}
};