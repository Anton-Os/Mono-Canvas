#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;

uniform uvec2 msTime;
uniform mat4 mvpMatrix;

layout(location = 0) out vec2 texCoord_out;
layout(location = 1) out uint vertexID_out;
layout(location = 2) out uint indexID_out;

void main(){
    vec4 wPos = vec4(pos, 1.0);
    texCoord_out = texCoord;
    vertexID_out = gl_VertexID;
    indexID_out = gl_InstanceID;
    gl_Position = mvpMatrix * wPos;
}