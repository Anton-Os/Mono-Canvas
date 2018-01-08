#version 440 core

layout(location = 0) in vec3 pos;
layout(location = 4) in vec2 texCoord;

uniform mat4 mvpMatrix;

layout(location = 0) out uint vertexID_out;
layout(location = 1) out vec2 texCoord_out;

void main(){
    vec4 wPos = vec4(pos, 1.0);
    vertexID_out = gl_VertexID;
    texCoord_out = texCoord;

    gl_Position = mvpMatrix * wPos;
}