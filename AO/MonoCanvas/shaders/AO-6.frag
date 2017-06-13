#version 330 core
in vec4 color_vert;
in vec4 boxishColors_vert;
in vec4 cubeColors_vert;
in vec2 texCoord_vert;

out vec4 color_frag;

void main() {
    vec4 colorFinal = cubeColors_vert;
    color_frag = vec4(colorFinal.r, colorFinal.g, colorFinal.b, colorFinal.a);
}
