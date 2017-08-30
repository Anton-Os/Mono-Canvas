#version 430 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

// layout(binding = 0) uniform sampler2D currentTexture;

layout(std430, binding = 1) buffer materialBlock {
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
};

layout(location = 0) out vec4 frag_out;

void main(){
    float diffuseStrength = -dot(normalize(vec3(pos)), normalize(normal));
    vec4 defaultColor = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 diffuseLight = vec4(
        diffuseColor.r * diffuseStrength,
        diffuseColor.g * diffuseStrength,
        diffuseColor.b * diffuseStrength,
        diffuseColor.a
    ); 
    frag_out = diffuseLight;
}