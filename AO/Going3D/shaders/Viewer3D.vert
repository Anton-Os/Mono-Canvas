#version 330 core
#pragma debug(on)

layout (location = 0) in vec3 cubePos;
layout (location = 1) in vec4 cubeColor;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec4 cubeColor_vert;

void main(){
    mat4 matrixFinal = Projection * View * Model;
    vec3 positionFinal = cubePos;
    cubeColor_vert = cubeColor;

    gl_Position = matrixFinal * vec4(positionFinal.x, positionFinal.y, positionFinal.z, 1.0f);
}
