#version 430 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) flat in uint renderMode;

// layout(binding = 0) uniform sampler2D currentTexture;

layout(std430, binding = 1) buffer materialBlock {
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
};

layout(location = 0) out vec4 frag_out;

void main(){
    if(renderMode == 1){
        frag_out = vec4(0.258, 0.525, 0.956, 1.0); 
    } else if(renderMode == 2){
        frag_out = vec4(0.341, 0.572, 0.949, 1.0);
    } else if(renderMode == 3){
        frag_out = vec4(0.219, 0.447, 0.819, 1.0);
    }
}