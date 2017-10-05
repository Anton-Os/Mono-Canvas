#version 430 core

layout(location = 0) in vec2 texCoord;

layout(location = 0) out vec4 frag_out;

void main(){
    frag_out = vec4(0.258, 0.525, 0.956, 0.7);
}