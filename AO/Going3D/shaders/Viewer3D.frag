#version 430 core
#pragma debug(on)

// Earlier Versions do not support the layout "binding" qualifier

in vec4 color_vert;
in vec2 texCoord_vert;

uniform int surfaceRenderMode;
layout(binding = 0) uniform sampler2D texture;

out vec4 output_frag;

void main(){
    if(surfaceRenderMode == 1){
        output_frag = vec4(color_vert.r * 0.65, color_vert.g * 0.65, color_vert.b * 0.65, color_vert.a);
		// Individual values are used to avoid reducing transparency to 0.65 the original
    } else if(surfaceRenderMode == 2){
		output_frag = vec4(color_vert.r + (1.0 - color_vert.r) / 2, color_vert.g + (1.0 - color_vert.g) / 2, color_vert.b + (1.0 - color_vert.b) / 2, color_vert.a);
	} else {
	    output_frag = color_vert;
	}
}
