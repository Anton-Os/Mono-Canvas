#version 430 core

layout(location = 0) in vec4 color;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

layout(binding = 0) uniform sampler2D currentTexture;
uniform vec4 defaultColor;
uniform uint surfaceRenderMode;

layout(location = 0) out vec4 output_frag;

void main(){
    vec4 presetColor = { 0.2588, 0.5254, 0.9568, 1.0 };
    output_frag = presetColor;
}