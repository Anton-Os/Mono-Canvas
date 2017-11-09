#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 6) in ivec2 state;

uniform mat4 mvpMatrix;

layout(location = 0) out uint vertexID_out;
layout(location = 1) out uint state_out;

void main(){
    vec4 wPos = vec4(pos, 1.0);
    vertexID_out = gl_VertexID;
    state_out = state[0];

    gl_Position = mvpMatrix * wPos;
}