#version 430 core

layout(location = 0) in vec4 color;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

layout (std140, binding = 1) uniform fragmentBlock {
    float ambientLightStrength;
    uint surfaceRenderMode;
};

layout(location = 0) out vec4 output_frag;

void main(){
    output_frag = color;
}