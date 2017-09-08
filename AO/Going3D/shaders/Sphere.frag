#version 430

layout(location = 0) in vec2 texCoord;
layout(location = 1) in vec3 normal;
layout(location = 2) in flat uint vertexID;

uniform sampler2D sphereTex;
uniform uint renderMode;

layout(std430, binding = 1) buffer colorPalette {
	vec3 color1;
	vec3 color2;
	vec3 color3;
	vec3 color4;
};

layout(location = 0) out vec4 frag_out;

void main(){
	if(renderMode == 1){
		if(vertexID % 12 >= 9) frag_out = vec4(color1, 1.0);
		else if(vertexID % 12 >= 6) frag_out = vec4(color2, 1.0);
		else if(vertexID % 12 >= 3) frag_out = vec4(color3, 1.0);
		else frag_out = vec4(color4, 1.0);
	} else {
		frag_out = vec4(0.258, 0.525, 0.956, 1.0);
	}
}