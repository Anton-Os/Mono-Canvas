#version 430 core

layout(location = 0) in flat uint vertexID;

uniform uint renderMode;

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
        frag_out = vec4(0.8, 0.3, 0.1, 1.0);
    } else if(renderMode == 2){
        if(vertexID % 3 == 1) frag_out = vec4(grey2, 0.7);
        else if(vertexID % 3 == 2) frag_out = vec4(grey3, 0.7);
        else frag_out = vec4(grey4, 0.7);    
    } else {
        if(vertexID % 3 == 1) frag_out = vec4(red, 0.7);
        else if(vertexID % 3 == 2) frag_out = vec4(green, 0.7);
        else frag_out = vec4(blue, 0.7);
    }
}