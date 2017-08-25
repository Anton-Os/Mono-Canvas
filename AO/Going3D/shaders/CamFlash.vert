#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 txc;
layout(location = 2) in vec3 nrm;

uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;
uniform mat3 nMatrix;

layout(location = 0) out vec4 pos_out;
layout(location = 1) out vec2 txc_out;
layout(location = 2) out vec3 nrm_out;

void main(){
    pos_out = mvMatrix * vec4(pos.x, pos.y, pos.z, 1.0);
    txc_out = txc;
    nrm_out = nMatrix * nrm;

    gl_Position = mvpMatrix * vec4(pos.x, pos.y, pos.z, 1.0);
}