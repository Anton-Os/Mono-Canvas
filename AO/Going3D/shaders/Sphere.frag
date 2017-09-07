#version 430

layout(location = 0) in vec2 texCoord;
layout(location = 1) in vec3 normal;

uniform sampler2D sphereTex;
uniform uint renderMode;

layout(location = 0) out vec4 frag_out;

void main(){
	if(renderMode == 1){
		// Textured Sphere
	} else {
		frag_out = vec4(0.258, 0.525, 0.956, 1.0);
	}
}