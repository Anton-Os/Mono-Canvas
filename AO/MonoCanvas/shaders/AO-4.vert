#version 330 core
#pragma debug(on)

layout (location = 0) in vec3 position;
layout (location = 3) in vec3 position2;
layout (location = 1) in vec4 color;
layout (location = 4) in vec4 color2;
layout (location = 2) in vec2 texCoord;

uniform mat4 Projection;

out vec4 color_vert;
out vec2 texCoord_vert;

void main() {
    color_vert = color2;
    texCoord_vert = texCoord;
    gl_Position = /* Projection */ vec4(position2.x, position2.y, position2.z, 1.0f);
}
