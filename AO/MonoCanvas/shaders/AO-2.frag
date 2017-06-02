#version 330 core
in vec4 color_vert;
in vec2 texCoord_vert;

uniform sampler2D container;

out vec4 color_frag;

void main() {
    color_frag = texture(container, texCoord_vert);
}
