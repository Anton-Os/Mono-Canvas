#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;

uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;
uniform mat3 nMatrix;

layout(location = 0) out vec2 texCoord_out;
layout(location = 1) out vec3 normal_out;

void main() {
	vec4 wPos = vec4(pos.x, pos.y, pos.z, 1.0);
    texCoord_out = texCoord;
    normal_out = nMatrix * normalize(pos);

	gl_Position = mvpMatrix * wPos;
}