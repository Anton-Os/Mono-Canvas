#version 430

layout(location = 0) in vec2 texCoord;
layout(location = 1) in vec3 normal;
layout(location = 2) in flat uint vertexID;

layout(binding = 0) uniform sampler2D sphereTex;
uniform uvec2 sphereParams;
uniform uint renderMode;

layout(std430, binding = 1) buffer colorPalette {
	float color1[3];
	float color2[3];
	float color3[3];
	float color4[3];
};


layout(location = 0) out vec4 frag_out;

void main(){
	if(renderMode == 1){
		if(vertexID % 12 >= 9) frag_out = vec4(color1[0], color1[1], color1[2], 1.0);
		else if(vertexID % 12 >= 6) frag_out = vec4(color2[0], color2[1], color2[2], 1.0);
		else if(vertexID % 12 >= 3) frag_out = vec4(color3[0], color3[1], color3[2], 1.0);
		else frag_out = vec4(color4[0], color4[1], color4[2], 1.0);
	} else if(renderMode == 2){
		frag_out = texture(sphereTex, texCoord);
	} else if(renderMode == 3){ 
		// float intensity = (1.0 / float(sphereParams[1])) * mod(vertexID, sphereParams[1]);
		float intensity = (1.0 / float(sphereParams[1])) * 3;
	 	frag_out = vec4(intensity, intensity, intensity, 1.0);
		// frag_out = vec4(0.55, 0.66, 0.956, 1.0);
	} else {
		frag_out = vec4(0.258, 0.525, 0.956, 0.7);
	}
}