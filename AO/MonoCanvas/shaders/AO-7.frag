#version 330 core
#pragma debug(on)

in vec4 fcolor;

layout(location = 0) out vec4 FragColor;

void main() {
   FragColor = fcolor;
}
