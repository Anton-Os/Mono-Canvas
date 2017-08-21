#version 430 core

layout(location = 0) in vec4 color;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

layout(binding = 0) uniform sampler2D currentTexture;

layout (std430, binding = 1) buffer testBlock {
    float Red;
    float Green;
    float Blue;
};

/* layout(std430, binding = 2) buffer materialBlock {
    float ambientColor[4];
    float diffuseColor[4];
    float specularColor[4];
}; */

layout(std430, binding = 2) buffer materialBlock {
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
};

/* layout(std140, binding = 2) uniform lightSourceBlock {
    float lightIntensity;
    float lightRadius;
    vec4 lightAbsoluteLocation;
}; */

layout(location = 0) out vec4 output_frag;

void main(){
    // vec4 presetColor = vec4(0.2, Green, Blue, 1.0);
    // vec4 presetColor = vec4(diffuseColor[0], diffuseColor[1], diffuseColor[2], diffuseColor[3]);
    vec4 presetColor = vec4(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
    output_frag = presetColor;
}