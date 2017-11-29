#version 430 core

layout(location = 0) in vec3 pos;

uniform mat4 mvpMatrix;
uniform uint primMode;
uniform float waveHeight;
uniform float waveInc;

layout(location = 0) out uint vertexID_out;

void main(){

    float zNew = abs(sin(pos.z + waveInc)) * waveHeight;
    vec4 wPos = vec4(pos.x, pos.y, zNew, 1.0);

    vertexID_out = gl_VertexID;
    gl_Position = mvpMatrix * wPos;
}