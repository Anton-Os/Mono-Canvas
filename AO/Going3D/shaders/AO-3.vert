#version 330 core
#pragma debug(on)

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

uniform mat4 Projection;

out vec4 color_vert;

void main() {
    color_vert = color;
    gl_Position = Projection * vec4(position.x, position.y, position.z, 1.0f);
}
