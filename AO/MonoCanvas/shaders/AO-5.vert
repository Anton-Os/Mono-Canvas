#version 330 core
#pragma debug(on)

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 boxishShape;

uniform mat4 Projection;

out vec4 color_vert;
out vec2 texCoord_vert;

void main() {
    vec3 positionFinal = boxishShape; // To avoid trouble on gl_Position
    color_vert = color;
    texCoord_vert = texCoord;

    gl_Position = Projection * vec4(positionFinal.x, positionFinal.y, positionFinal.z, 1.0f);
}
