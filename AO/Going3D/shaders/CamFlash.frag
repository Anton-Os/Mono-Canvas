#version 430 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 txc;
layout(location = 2) in vec3 nrm;

layout(binding = 0) uniform sampler2D currentTexture;

layout(std430, binding = 1) buffer materialBlock {
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
};

layout(location = 0) out vec4 out_frag;

void main(){
    float diffuseStrength = dot(nrm, normalize(vec3(pos)));
    // float diffuseStrength = distance(pos, cameraPos);
    // float diffuseFactor = 5;
    vec4 diffuseLight = + vec4(
        diffuseColor.r * diffuseStrength,
        diffuseColor.g * diffuseStrength,
        diffuseColor.b * diffuseStrength,
        diffuseColor.a
    );
    out_frag = diffuseLight;
}