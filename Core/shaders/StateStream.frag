#version 430 core

layout(location = 0) in flat uint vertexID;
layout(location = 1) in flat uint state;
// layout(location = 1) in flat float state;

layout(location = 0) out vec4 frag_out;

void main(){
    vec3 black = vec3(0.0, 0.0, 0.0);
    vec3 lightGrey = vec3(0.95, 0.95, 0.95);
    vec3 white = vec3(1.0, 1.0, 1.0);

    vec3 red = vec3(1.0, 0.0, 0.0);
    vec3 yellow = vec3(1.0, 1.0, 0.39);
    vec3 green = vec3(0.0, 1.0, 0.6);
    vec3 blue = vec3(0.3, 0.5, 0.9);
    vec3 pink = vec3(0.95, 0.25, 0.62);
    vec3 brown = vec3(0.44, 0.35, 0.28);
    
    if(state == 1){ // ALIVE
        frag_out = vec4(white, 1.0);
    } else if (state == 2){ // DEAD
        frag_out = vec4(red, 1.0);
    } else if (state == 3){ // BORN
        frag_out = vec4(green, 1.0);
    } else if (state == 4){ // QUICKDEAD
        frag_out = vec4(yellow, 1.0);
    } else { // UNTOUCHED
        if(vertexID % 2 == 0) frag_out = vec4(white, 0.2);
        else frag_out = vec4(white, 0.15);
    }
}