#version 430 core

layout(location = 0) in flat uint vertexID;
layout(location = 1) in vec3 rgbScale;

uniform uint renderMode;

layout(location = 0) out vec4 frag_out;

void main(){
    frag_out = vec4(rgbScale, 1.0);
}