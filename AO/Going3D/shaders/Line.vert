#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

uniform mat4 mvpMatrix;

layout(location = 0) out vec3 color_out;

void main(){
    color_out = color;
    gl_Position = mvpMatrix * vec4(pos, 1.0);
}