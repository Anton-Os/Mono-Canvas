#version 430 core
#pragma debug(on)

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec4 color_vert;
out vec2 texCoord_vert;

void main(){
    mat4 matrixFinal = Projection * View * Model;
    vec3 positionFinal = pos;
    color_vert = color;
	texCoord_vert = texCoord;

    gl_Position = matrixFinal * vec4(positionFinal.x, positionFinal.y, positionFinal.z, 1.0f);
}