#version 430 core
#pragma debug(on)

layout (location = 0) in vec4 color;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec4 worldPos;

uniform float ambientLightStrength;
uniform vec3 cameraPos;
uniform vec3 worldLightColor;
uniform vec3 lightSourcePos;

out vec4 output_frag;

vec3 computeReflection(vec3 l, vec3 n){
	vec3 reflection = (2 * dot(l, n)) * n - l;
	return reflection;
}

void main(){
    float diffuseIntensity = 1.0;
    float specularIntensity = 0.3;
    vec4 colorFinal = vec4(84.0 / 255.0, 157.0 / 255.0, 234.0 / 255.0, 1.0);

    vec3 diffuseLightDirection = normalize(lightSourcePos - vec3(worldPos.x, worldPos.y, worldPos.z));
    float diffuseLightStrength = max(0.25, min(dot(normals, diffuseLightDirection), 1.0));

    // Compute Specular Light Here
	vec3 viewerDirection = normalize(cameraPos - vec3(worldPos.x, worldPos.y, worldPos.z));
	vec3 specularLightDirection = normalize(computeReflection(diffuseLightDirection, normals));
	float specularLightStrength = min(dot(viewerDirection, specularLightDirection), 1.0);

    vec4 ambientLight = vec4(worldLightColor.r * ambientLightStrength,
                             worldLightColor.g * ambientLightStrength,
                             worldLightColor.b * ambientLightStrength,
                             1.0);
    vec4 diffuseLight = vec4(worldLightColor.r * diffuseLightStrength * diffuseIntensity,
                             worldLightColor.g * diffuseLightStrength * diffuseIntensity,
                             worldLightColor.b * diffuseLightStrength * diffuseIntensity,
                             1.0);
    vec4 specularLight = vec4(worldLightColor.r * specularLightStrength * specularIntensity,
                              worldLightColor.g * specularLightStrength * specularIntensity,
                              worldLightColor.b * specularLightStrength * specularIntensity,
                              1.0);

    output_frag = colorFinal * (ambientLight + specularLight);
}
