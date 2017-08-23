#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

layout(binding = 0) uniform sampler2D currentTexture;
uniform vec3 cameraPos;

layout(std430, binding = 1) buffer materialBlock {
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
};
layout(std430, binding = 2) buffer lightSourceBlock {
    float lightRadius;
    vec3 lightAbsLoc;
};

layout(location = 0) out vec4 output_frag;

void main(){
    vec3 diffuseLightDirection = normalize(cameraPos - pos);
    // float diffuseStrength = min(dot(normal, viewDirection), 1.0);
    float diffuseStrength = dot(normal, diffuseLightDirection) * 6.0;
    vec4 diffuseLight = + vec4(
        diffuseColor.r * diffuseStrength,
        diffuseColor.g * diffuseStrength,
        diffuseColor.b * diffuseStrength,
        diffuseColor.a
    );
    output_frag = diffuseLight;
}