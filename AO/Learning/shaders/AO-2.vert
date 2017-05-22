#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec4 texCoord;

out vec4 color_vert;
out vec4 texCoord_vert;

void main() {
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
    color_vert = color;
    texCoord_vert = texCoord;
}
