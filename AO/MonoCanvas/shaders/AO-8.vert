#version 330 core
#pragma debug(on)

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 boxishVerts;
layout (location = 4) in vec4 boxishColors;

layout (location = 5) in vec3 cubeVerts;
layout (location = 6) in vec4 cubeColors;
layout (location = 7) in vec2 cubeTexCoord;

uniform mat4 Projection;
uniform mat4 View;
// uniform mat4 Look;
// uniform mat4 Reposition;

out vec4 color_vert;
out vec4 boxishColors_vert;
out vec4 cubeColors_vert;
out vec2 texCoord_vert;
out vec2 cubeTexCoord_vert;

void main() {
    vec3 positionFinal = cubeVerts;
    mat4 matrixFinal = Projection * View;

    color_vert = color;
    boxishColors_vert = boxishColors;
    cubeColors_vert = cubeColors;
    texCoord_vert = texCoord;
    cubeTexCoord_vert = cubeTexCoord;

    gl_Position = matrixFinal * vec4(positionFinal.x, positionFinal.y, positionFinal.z, 1.0f);
}
