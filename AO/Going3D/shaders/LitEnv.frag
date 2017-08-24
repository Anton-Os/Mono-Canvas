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
    vec3 viewDirection = normalize(pos - cameraPos);
    // float diffuseStrength = dot(normal, viewDirection);
    float diffuseStrength = distance(pos, cameraPos);
    float diffuseFactor = 5;
    vec4 diffuseLight = + vec4(
        diffuseColor.r * diffuseStrength / diffuseStrength,
        diffuseColor.g * diffuseStrength / diffuseStrength,
        diffuseColor.b * diffuseStrength / diffuseStrength,
        diffuseColor.a
    );
    if(cameraPos == vec3(0.0, 0.0, -100.0)){
        output_frag = vec4(0.0, 0.0, 1.0, 1.0);
    } else if(diffuseStrength < 300.0){
        output_frag = vec4(1.0, 0.0, 0.0, 1.0);
    } else {
        output_frag = vec4(0.0, 1.0, 0.0, 1.0);
    }
    //output_frag = diffuseLight;
}