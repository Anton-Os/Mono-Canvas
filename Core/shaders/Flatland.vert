#version 440 core

layout(location = 1) in vec2 pos_2f;

void main(){
    vec4 wPos = vec4(pos_2f, 0.3, 1.0);

    gl_Position =  wPos;
}