#version 440 core

layout(location = 0) in flat uint vertexID;

uniform int state;

layout(location = 0) out vec4 frag_out;

void main(){
    if(state == 0)
        frag_out = vec4(0.8, 0.3, 0.1, 1.0);
    else
        frag_out = vec4(0.0, 0.0, 0.0, 1.0);
}