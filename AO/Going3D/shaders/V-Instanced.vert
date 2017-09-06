#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;
uniform mat3 nMatrix;

layout(location = 0) out vec4 pos_out;
layout(location = 1) out vec2 texCoord_out;
layout(location = 2) out vec3 normal_out;
layout(location = 3) out uint renderMode_out;

void main(){
    vec4 wPos = vec4(pos.x, pos.y, pos.z, 1.0);
    pos_out = mvMatrix * wPos;
    texCoord_out = texCoord;
    normal_out = nMatrix * normal;

    if(gl_VertexID % 9 >= 6){
        renderMode_out = 1;
    } else if(gl_VertexID % 9 >= 3){
        renderMode_out = 2;
    } else if(gl_VertexID % 9 >= 0){
        renderMode_out = 3;
    }

    gl_Position = mvpMatrix * wPos;
}