#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 worldMatrix;
uniform mat4 localMatrix;

layout(location = 1) out vec2 texCoord_out;
layout(location = 2) out vec3 normal_out;

void main(){
    texCoord_out = texCoord;
    normal_out = normal;

    gl_Position = worldMatrix * localMatrix * vec4(pos.x, pos.y, pos.z, 1.0);
}