#version 430 core
#pragma debug(on)

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normals;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

layout (location = 0) out vec4 color_vert;
layout (location = 1) out vec2 texCoord_vert;
layout (location = 2) out vec3 normals_vert;
layout (location = 3) out vec3 fragPos_vert;

void main(){
    mat4 matrixFinal = Projection * View * Model;
    vec3 positionFinal = pos;

	texCoord_vert = texCoord;
    color_vert = color;
	normals_vert = normals;
	fragPos_vert = vec3(Model * vec4(pos.x, pos.y, pos.z, 1.0));

    gl_Position = matrixFinal * vec4(positionFinal.x, positionFinal.y, positionFinal.z, 1.0f);
}
