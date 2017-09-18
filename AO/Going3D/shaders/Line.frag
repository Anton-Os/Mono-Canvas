#version 430 core

layout(location = 0) in vec3 color;

layout(location = 0) out vec4 frag_out;

void main(){
    // frag_out = vec4(color, 1.0);
    frag_out = vec4(1.0, 1.0, 1.0, 1.0);
}