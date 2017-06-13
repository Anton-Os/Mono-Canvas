/* ------------------ GL VERTEX SHADER ------------------ */

#version 450 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vPosition1;
layout(location = 2) in vec4 vPosition2;
layout(location = 3) in vec4 fColor;

out vec4 fColor_VERT;
out vec4 fColor2_VERT;
out vec4 allVectors = vPosition + vPosition1 + vPosition2;

void main() {
    fColor_VERT = fColor;
    fColor2_VERT = vec4(60.0 / 255.0, 119.0 / 255.0, 214.0 / 255.0, 1.0);

    // gl_Position = vPosition + vPosition1 + vPosition2;
    gl_Position = vPosition;
}
