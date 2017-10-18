#version 430 core

layout(location = 0) in vec2 texCoord;
layout(location = 1) in flat uint vertexID;

uniform uint renderMode;

layout(location = 0) out vec4 frag_out;

void main(){
    /* vec3 color1 = vec3(0.219, 0.447, 0.819);
    vec3 color2 = vec3(0.243, 0.4, 0.76);
    vec3 color3 = vec3(0.466, 0.615, 0.819);
    vec3 color4 = vec3(0.76, 0.913, 0.96); */

    vec3 grey0 = vec3(0.1, 0.1, 0.1);
    vec3 grey1 = vec3(0.35, 0.35, 0.35);
    vec3 grey2 = vec3(0.5, 0.5, 0.5);
    vec3 grey3 = vec3(0.65, 0.65, 0.65);
    vec3 grey4 = vec3(0.8, 0.8, 0.8);
    vec3 grey5 = vec3(0.95, 0.95, 0.95);

    vec3 tomatoRed = vec3(1.0, 0.4, 0.4);
    vec3 mintGreen = vec3(0.0, 1.0, 0.6);
    vec3 deepBlue = vec3(0.3, 0.5, 0.9);
    
    vec4 defaultColor = vec4(0.258, 0.525, 0.956, 0.7);

    /* if(vertexID % 4 == 1) frag_out = vec4(color1.r, color1.g, color1.b, 1.0);
    else if(vertexID % 4 == 2) frag_out = vec4(color2.r, color2.g, color2.b, 1.0);
	else if(vertexID % 4 == 3) frag_out = vec4(color3.r, color3.g, color3.b, 1.0);
	else frag_out = vec4(color4.r, color4.g, color4.b, 1.0); */

    if(renderMode == 1){
        if(vertexID % 3 == 1) frag_out = vec4(grey0, 1.0);
        else if(vertexID % 3 == 2) frag_out = vec4(grey2, 1.0);
        else frag_out = vec4(grey5, 1.0);
    } else if (renderMode == 2){
        if(vertexID % 3 == 1) frag_out = vec4(tomatoRed.r, tomatoRed.g, tomatoRed.b, 1.0);
        else if(vertexID % 3 == 2) frag_out = vec4(mintGreen.r, mintGreen.g, mintGreen.b, 1.0);
        else frag_out = vec4(deepBlue.r, deepBlue.g, deepBlue.b, 1.0);
    } else {
        frag_out = defaultColor;
    }
}