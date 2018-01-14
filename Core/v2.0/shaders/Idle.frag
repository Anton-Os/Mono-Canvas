#version 440 core

layout(location = 0) in vec4 color;

layout(location = 0) out vec4 frag_out;

void main(){
    frag_out = color;
    /* frag_out = vec4(1.0, 1.0, 0.0, 1.0); */
}