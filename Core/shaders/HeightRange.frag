#version 430 core

layout(location = 0) in vec2 texCoord;
layout(location = 1) in flat uint vertexID;
layout(location = 2) in float posZ;

uniform uint renderMode;
uniform float heightRange[2];
uniform float rise;

layout(location = 0) out vec4 frag_out;

void main(){
    vec3 white = vec3(1.0, 1.0, 1.0);
    vec3 lightGrey = vec3(0.8, 0.8, 0.8);
    vec3 medGrey = vec3(0.5, 0.5, 0.5);
    vec3 darkGrey = vec3(0.2, 0.2, 0.2);

    vec3 color1 = vec3(0.0, 1.0, 0.6);
    vec3 color2 = vec3(1.0, 0.4, 0.4);
    vec3 color3 = vec3(0.3, 0.5, 0.9);

    /* if(vertexID % 3 == 1) frag_out = vec4(color1.r, color1.g, color1.b, 1.0);
    else if(vertexID % 3 == 2) frag_out = vec4(color2.r, color2.g, color2.b, 1.0);
	else frag_out = vec4(color3.r, color3.g, color3.b, 1.0); */

    float heightMax = rise / 2;
    float heightMin = -1 * heightMax;
    if(renderMode == 1){
        float heightClamp = (posZ + heightMax) / (heightMax - heightMin);
        vec3 colorClamp = medGrey + (vec3(0.1, 0.1, 0.1) * heightClamp);
        frag_out = vec4(colorClamp, 1.0);
    } else if(renderMode == 2){
        float heightClamp = (posZ + heightMax) / (heightMax - heightMin);
        vec3 colorClamp = darkGrey + ((lightGrey - darkGrey) * heightClamp);
        frag_out = vec4(colorClamp, 1.0);
    } else {
        if(vertexID % 3 == 1) frag_out = vec4(color1.r, color1.g, color1.b, 1.0);
        else if(vertexID % 3 == 2) frag_out = vec4(color2.r, color2.g, color2.b, 1.0);
	    else frag_out = vec4(color3.r, color3.g, color3.b, 1.0); 
    }
}