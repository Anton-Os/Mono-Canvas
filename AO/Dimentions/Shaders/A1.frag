/* ------------------ GL FRAGMENT SHADER ------------------ */

#version 450 core

in vec4 fColor_VERT;
in vec4 fColor2_VERT;

out vec4 fColor_FRAG;

void main(){
    /* fragColor = vec4(60.0 / 255.0, 119.0 / 255.0, 214.0 / 255.0, 1.0); */
    fColor_FRAG = fColor_VERT;
}

// HELLO
