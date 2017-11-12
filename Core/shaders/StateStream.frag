#version 430 core

layout(location = 0) in flat uint vertexID;
layout(location = 1) in flat uint state;
// layout(location = 1) in flat float state;

layout(location = 0) out vec4 frag_out;

void main(){
    vec3 black = vec3(0.0, 0.0, 0.0);
    vec3 lightGrey = vec3(0.95, 0.95, 0.95);
    vec3 white = vec3(1.0, 1.0, 1.0);

    vec3 red = vec3(1.0, 0.4, 0.4);
    vec3 green = vec3(0.0, 1.0, 0.6);
    vec3 blue = vec3(0.3, 0.5, 0.9);
    
    if(state == 1){
        frag_out = vec4(white, 1.0);
    } else if (state == 2){
        frag_out = vec4(green, 1.0);
    } else if (state == 3){
        frag_out = vec4(blue, 1.0);
    } else {
        if(vertexID % 2 == 0) frag_out = vec4(black, 1.0);
        else frag_out = vec4(black, 0.5);
    }
}