#version 430 core
#pragma debug(on)

layout (location = 0) in vec4 color;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec4 worldPos;

uniform float ambientLightStrength;
uniform vec3 worldLightColor;
uniform vec3 lightSourcePos;

out vec4 output_frag;

void main(){
    // vec4 colorFinal = color;
    vec4 colorFinal = vec4(84.0 / 255.0, 157.0 / 255.0, 234.0 / 255.0, 1.0); // override original

    vec3 diffuseLightDirection = normalize(lightSourcePos - vec3(worldPos.x, worldPos.y, worldPos.z));
    // float diffuseLightStrength = max(dot(normals, diffuseLightDirection), ambientLightStrength);
	float diffuseLightStrength = dot(normals, diffuseLightDirection); // override original

    vec4 ambientLight = vec4(worldLightColor.r * ambientLightStrength,
                             worldLightColor.g * ambientLightStrength,
                             worldLightColor.b * ambientLightStrength,
                             1.0);
    vec4 diffuseLight = vec4(worldLightColor.r * diffuseLightStrength,
                             worldLightColor.g * diffuseLightStrength,
                             worldLightColor.b * diffuseLightStrength,
                             1.0);
    // output_frag = colorFinal * (ambientLight + diffuseLight);
	output_frag = colorFinal * (ambientLight + diffuseLight);
}