#version 440 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;

layout(location = 1) out vec4 color_out;

void main(){
    color_out = color;

    vec4 wPos = vec4(pos, 1.0);

    gl_Position =  wPos;
}