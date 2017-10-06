#version 430 core

layout(location = 0) in vec2 texCoord;
layout(location = 1) in flat uint vertexID;

layout(location = 0) out vec4 frag_out;

void main(){
    vec3 color1 = vec3(0.219, 0.447, 0.819);
    vec3 color2 = vec3(0.243, 0.4, 0.76);
    vec3 color3 = vec3(0.466, 0.615, 0.819);
    vec3 color4 = vec3(0.76, 0.913, 0.96);
    // frag_out = vec4(0.258, 0.525, 0.956, 0.7);
    if(vertexID % 12 >= 9) frag_out = vec4(color1.r, color1.g, color1.b, 1.0);
    else if(vertexID % 12 >= 6) frag_out = vec4(color2.r, color2.g, color2.b, 1.0);
	else if(vertexID % 12 >= 3) frag_out = vec4(color3.r, color3.g, color3.b, 1.0);
	else frag_out = vec4(color4.r, color4.g, color4.b, 1.0);
}