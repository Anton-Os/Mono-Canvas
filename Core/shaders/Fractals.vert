#version 430 core

layout(location = 0) in vec3 pos;

uniform mat4 mvpMatrix;

layout(location = 0) out uint vertexID_out;
layout(location = 1) out vec4 pos_out;

void main(){
    vec4 wPos = vec4(pos, 1.0);
    vertexID_out = gl_VertexID;

    pos_out = wPos;
    gl_Position = mvpMatrix * wPos;
    // gl_Position = wPos;
}