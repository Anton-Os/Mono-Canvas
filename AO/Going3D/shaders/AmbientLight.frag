#version 430 core
#pragma debug(on)

// Earlier Versions of GLSL do not support the layout "binding" qualifier

in vec4 color_vert;
in vec2 texCoord_vert;

uniform int surfaceRenderMode;
uniform float ambientStrength;
layout(binding = 0) uniform sampler2D currentTexture;

out vec4 output_frag;

void main(){
  vec3 ambientColor = ambientStrength * vec3(1.0, 1.0, 1.0);
  vec4 ambientLight = vec4(ambientColor.r, ambientColor.g, ambientColor.b, 1.0);
	vec4 color_frag;
    if(surfaceRenderMode == 1){
        color_frag = vec4(color_vert.r * 0.65, color_vert.g * 0.65, color_vert.b * 0.65, color_vert.a);
		// Individual values are used to avoid reducing transparency to 0.65 the original
    } else if(surfaceRenderMode == 2){
		color_frag = vec4(color_vert.r + (1.0 - color_vert.r) / 2,
                          color_vert.g + (1.0 - color_vert.g) / 2, 
                          color_vert.b + (1.0 - color_vert.b) / 2,
                          color_vert.a);
    } else if(surfaceRenderMode == 3){
		color_frag = texture(currentTexture, texCoord_vert);
	} else {
        color_frag = color_vert;
	}
    
  output_frag = color_frag * ambientLight;
}
