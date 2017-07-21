#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

layout(location = 0) out vec4 color_out;
layout(location = 1) out vec2 texCoord_out;
layout(location = 2) out vec3 normal_out;

void main(){
    color_out = color;
    texCoord_out = texCoord;
    normal_out = normal;

    gl_Position = vec4(pos.x, pos.y, pos.z, 9.0);
}