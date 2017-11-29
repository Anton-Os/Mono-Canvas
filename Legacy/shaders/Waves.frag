#version 430 core

layout(location = 0) in flat uint vertexID;

uniform uint renderMode;

layout(location = 0) out vec4 frag_out;

void main(){

    vec3 sand1 = vec3(0.929, 0.882, 0.607);
    vec3 sand2 = vec3(0.9, 0.9, 0.68);
    vec3 sand3 = vec3(0.95, 0.8, 0.65);
    
    vec3 blue = vec3(0.3, 0.5, 0.9);
    
    if(renderMode == 1){
        if(vertexID % 3 == 1) frag_out = vec4(sand1, 0.8);
        else if(vertexID % 3 == 2) frag_out = vec4(sand2, 0.8);
        else frag_out = vec4(sand3, 0.8);
    } else {
        if(vertexID % 3 == 1) frag_out = vec4(blue.r, blue.g, blue.b, 0.6);
        else if(vertexID % 3 == 2) frag_out = vec4(blue.r, blue.g, blue.b * 1.15, 0.6);
        else frag_out = vec4(blue.r * 1.1, blue.g * 1.1, blue.b * 1.3, 0.6);
    }
}