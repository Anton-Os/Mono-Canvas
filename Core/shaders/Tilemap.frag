#version 440 core

layout(location = 0) in flat uint vertexID;
layout(location = 1) in vec2 texCoord;

layout(binding = 0) uniform sampler2D currentTexture;
uniform int state;

layout(location = 0) out vec4 frag_out;

vec2 calcTexCoord(uint currentVertex){
    const float uMin = 0.0;
    const float uMax = 1.0;
    const float vMin = 0.0;
    const float vMax = 1.0;

    if(currentVertex % 4 == 0) return vec2(uMin, vMin);
    else if(currentVertex % 4 == 1) return vec2(uMax, vMin);
    else if(currentVertex % 4 == 2) return vec2(uMin, vMax);
    else return vec2(uMax, vMax);
}

/* vec4 calcColor(uint currentVertex){
    if(currentVertex % 4 == 0) return vec4(0.0, 0.0, 0.0, 1.0);
    else if(currentVertex % 4 == 1) return vec4(1.0, 0.0, 0.0, 1.0);
    else if(currentVertex % 4 == 2) return vec4(0.0, 1.0, 0.0, 1.0);
    else return vec4(0.0, 0.0, 1.0, 1.0);
} */

vec4 calcColor(uint currentVertex){
    if(texCoord[0] != 0) return vec4(0.0, 0.0, 0.0, 1.0);
    else return vec4(1.0, 1.0, 1.0, 1.0);
}

void main(){
    if(state == 1)
        frag_out = texture(currentTexture, texCoord);
        // frag_out = calcColor(vertexID);
    else if(state == 2)
        frag_out = vec4(0.3, 0.8, 0.1, 1.0);
    else if(state == 3)
        frag_out = vec4(0.3, 0.1, 0.8, 1.0);    
    else
        frag_out = vec4(0.0, 0.0, 0.0, 1.0);
}