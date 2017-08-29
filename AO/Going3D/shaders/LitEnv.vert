#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;
uniform mat3 nMatrix;
uniform vec3 lightSourcePos;

layout(location = 0) out vec4 pos_out;
layout(location = 1) out vec2 texCoord_out;
layout(location = 2) out vec3 normal_out;
layout(location = 3) out vec4 lightSourcePos_out;

void main(){
    vec4 wPos = vec4(pos.x, pos.y, pos.z, 1.0);
    pos_out = mvMatrix * wPos;
    texCoord_out = texCoord;
    normal_out = nMatrix * normal;
    lightSourcePos_out = vec4(lightSourcePos.x, lightSourcePos.y, lightSourcePos.z, 1.0);

    gl_Position = mvpMatrix * wPos;
}