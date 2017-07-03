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

void main(){
    float diffuseIntensity = 0.9;
    float specularIntensity = 0.9;
    vec4 colorFinal = vec4(84.0 / 255.0, 157.0 / 255.0, 234.0 / 255.0, 1.0); // override original

    vec3 diffuseLightDirection = normalize(lightSourcePos - vec3(worldPos.x, worldPos.y, worldPos.z));
    float diffuseLightStrength = min(dot(normals, diffuseLightDirection), 1.0);

    vec3 viewerDirection = normalize(cameraPos - vec3(worldPos.x, worldPos.y, worldPos.z));
    vec3 reflectDirection = reflect(lightSourcePos, normals);
    float specularLightStrength = pow(max(dot(viewerDirection, reflectDirection), 0), 32);
    vec3 specular = specularIntensity * specularLightStrength * worldLightColor;

    vec4 ambientLight = vec4(worldLightColor.r * ambientLightStrength,
                             worldLightColor.g * ambientLightStrength,
                             worldLightColor.b * ambientLightStrength,
                             1.0);
    vec4 diffuseLight = vec4(worldLightColor.r * diffuseLightStrength * diffuseIntensity,
                             worldLightColor.g * diffuseLightStrength * diffuseIntensity,
                             worldLightColor.b * diffuseLightStrength * diffuseIntensity,
                             1.0);
    vec4 specularLight = vec4(specular.r, specular.g, specular.b, 1.0);
    // output_frag = colorFinal * (ambientLight * diffuseLight * specularLight);
    output_frag = colorFinal * ambientLight * diffuseLight;
}
