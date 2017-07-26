#version 430 core

layout(location = 0) in vec4 color;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform vec4 defaultColor;
uniform uint surfaceRenderMode;

layout(location = 0) out vec4 output_frag;

void main(){
    if(surfaceRenderMode == 1){
        output_frag = vec4(defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
    } else if(surfaceRenderMode == 2){
        output_frag = vec4(color.r, color.g, color.b, color.a);
    }
}