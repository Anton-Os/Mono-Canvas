#version 430 core

layout(location = 0) in vec4 color;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

layout(binding = 0) uniform sampler2D currentTexture;
layout(std140, binding = 1) uniform materialBlock {
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
};
layout(std140, binding = 2) uniform lightSourceBlock {
    float lightIntensity;
    float lightRadius;
    vec4 lightAbsoluteLocation;
};

layout(location = 0) out vec4 output_frag;

void main(){
    vec4 presetColor = vec4(0.2, 0.2, 0.2, 1.0);
    output_frag = presetColor;
}