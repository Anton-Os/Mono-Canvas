#version 430 core

layout(location = 0) in vec2 texCoord;
layout(location = 1) in flat uint vertexID;

uniform uint renderMode;
uniform vec4 defaultColor;

layout(location = 0) out vec4 frag_out;

void main(){

    vec3 grey0 = vec3(0.05, 0.05, 0.05);
    vec3 grey1 = vec3(0.35, 0.35, 0.35);
    vec3 grey2 = vec3(0.5, 0.5, 0.5);
    vec3 grey3 = vec3(0.65, 0.65, 0.65);
    vec3 grey4 = vec3(0.95, 0.95, 0.95);

    vec3 red = vec3(1.0, 0.4, 0.4);
    vec3 green = vec3(0.0, 1.0, 0.6);
    vec3 blue = vec3(0.3, 0.5, 0.9);
    
    if(renderMode == 1){
        frag_out = vec4(grey4, 1.0);
    } else if (renderMode == 2){
        frag_out = vec4(grey0, 1.0);
    } else if (renderMode == 3){
        frag_out = vec4(grey2, 1.0);
    } else {
        if(vertexID % 3 == 1) frag_out = vec4(red, 1.0);
        else if(vertexID % 3 == 2) frag_out = vec4(green, 1.0);
        else frag_out = vec4(blue, 1.0);
    }
}