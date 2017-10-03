#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;

uniform uvec2 msTime;
uniform mat4 mvpMatrix;

layout(location = 0) out vec2 texCoord_out;

void main(){
    vec4 wPos = vec4(pos, 1.0);
    texCoord_out = texCoord;
    gl_Position = mvpMatrix * wPos;
}