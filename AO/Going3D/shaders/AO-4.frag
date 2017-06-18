#version 330 core
in vec4 color_vert;
in vec2 texCoord_vert;

uniform sampler2D currentTexture;

out vec4 color_frag;

void main() {
    // color_frag = texture(currentTexture, texCoord_vert);
    color_frag = color_vert;
}
