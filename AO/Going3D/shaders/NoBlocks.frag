#version 430 core

layout(location = 0) in vec4 color;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

layout(binding = 0) uniform sampler2D currentTexture;
uniform vec4 defaultColor;
uniform uint surfaceRenderMode;

layout(location = 0) out vec4 output_frag;

void main(){
    if(surfaceRenderMode == 1){
        output_frag = vec4(defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
    } else if(surfaceRenderMode == 2){
        output_frag = vec4(color.r, color.g, color.b, color.a);
    } else if(surfaceRenderMode == 3){
        output_frag = texture(currentTexture, texCoord);
    } else if(surfaceRenderMode == 4){
        output_frag = vec4(0.2588, 0.5254, 0.9568, 0.7);
    }
}