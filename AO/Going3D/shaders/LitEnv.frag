#version 430 core
#pragma debug(on)

// Earlier Versions of GLSL do not support the layout "binding" qualifier

layout (location = 0) in vec4 color_vert;
layout (location = 1) in vec2 texCoord_vert;
layout (location = 2) in vec3 normals_vert;
layout (location = 3) in vec3 fragPos_vert;

layout (binding = 0) uniform sampler2D currentTexture;
uniform int surfaceRenderMode;
uniform float ambientStrength;
uniform vec3 lightSourceLoc;

out vec4 output_frag;

void main(){
    vec3 worldLightColor = ambientStrength * vec3(1.0, 1.0, 1.0);
    vec4 ambientLight = vec4(worldLightColor.r, worldLightColor.g, worldLightColor.b, 1.0);

    vec3 lightDirection = normalize(lightSourceLoc - fragPos_vert);
    float lightDiffuse = max(dot(normals_vert, lightDirection), 1.0);
    vec4 diffuseLight = vec4(worldLightColor.r * lightDiffuse,
                             worldLightColor.g * lightDiffuse,
                             worldLightColor.b * lightDiffuse,
                             1.0);
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
        
    output_frag = color_frag * (ambientLight + diffuseLight);
}
