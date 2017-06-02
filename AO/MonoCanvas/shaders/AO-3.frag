#version 330 core
in vec4 color_vert;

out vec4 color_frag;

void main()
{
    //color = uvec4(ourColor.r, ourColor.g, ourColor.b, 255);
    color_frag = vec4(color_vert.r, color_vert.g, color_vert.b, color_vert.a);
    // color = vec4(1.0, 0.0, 0.0, 1.0);
}
