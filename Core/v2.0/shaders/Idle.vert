#version 440 core

layout(location = 0) in vec3 pos;

void main(){
    vec4 wPos = vec4(pos, 1.0);

    gl_Position =  wPos;
}