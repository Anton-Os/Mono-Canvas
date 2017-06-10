#version 330 core
in vec4 color_vert;
in vec4 boxishColors_vert;
in vec2 texCoord_vert;

out vec4 color_frag;

void main()
{
    vec4 colorFinal = boxishColors_vert;
    //color = uvec4(ourColor.r, ourColor.g, ourColor.b, 255);
    color_frag = vec4(colorFinal.r, colorFinal.g, colorFinal.b, colorFinal.a);
    // color = vec4(1.0, 0.0, 0.0, 1.0);
}
