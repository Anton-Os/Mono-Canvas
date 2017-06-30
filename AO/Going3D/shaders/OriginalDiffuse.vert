#version 430 core
#pragma debug(on)

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normals;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

layout (location = 0) out vec4 color_out;
layout (location = 1) out vec2 texCoord_out;
layout (location = 2) out vec3 normals_out;
layout (location = 3) out vec4 worldPos_out;

void main(){
    color_out = color;
    texCoord_out = texCoord;
    normals_out = normals;
    worldPos_out = Model * vec4(pos, 1.0);

    vec3 posFinal = pos;
    mat4 matrixFinal = Projection * View * Model;

    gl_Position = matrixFinal * vec4(posFinal.x, posFinal.y, posFinal.z, 1.0);
}