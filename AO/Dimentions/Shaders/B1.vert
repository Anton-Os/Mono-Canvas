/* ------------------ GL VERTEX SHADER ------------------ */

#version 450 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 fColor;
layout(location = 2) in vec4 vPosition2;
layout(location = 3) in vec4 fColor2;
layout(location = 4) in vec4 vPosition3;

out vec4 fColor_VERT;
out vec4 fColor2_VERT;

void main() {
    fColor_VERT = fColor;
    fColor2_VERT = fColor2;

    // gl_Position = vPosition + vPosition1 + vPosition2;
    gl_Position = vPosition3;
}