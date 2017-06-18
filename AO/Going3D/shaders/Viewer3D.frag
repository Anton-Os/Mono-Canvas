#version 330 core
#pragma debug(on)

in vec4 cubeColor_vert;

out vec4 output_frag;

void main(){
    output_frag = cubeColor_vert;
}
