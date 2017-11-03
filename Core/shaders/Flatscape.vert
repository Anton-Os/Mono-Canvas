#version 430 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 texCoord;

uniform mat4 mvpMatrix;

layout(location = 0) out vec2 texCoord_out;
layout(location = 1) out uint vertexID_out;

void main(){
    vec4 wPos = vec4(pos, 0.0, 1.0);
    texCoord_out = texCoord;
    vertexID_out = gl_VertexID;

    // gl_Position = mvpMatrix * wPos;
    gl_Position = wPos;
}