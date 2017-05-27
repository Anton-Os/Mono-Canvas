#version 330 core
#pragma debug(on)

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 color_vert;
out vec2 texCoord_vert;

void main() {
    vec2 reduceHalf = vec2(0.5, 0.5);

    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
    color_vert = color;
    // texCoord_vert = texCoord * reduceHalf;
    texCoord_vert = texCoord;
}
