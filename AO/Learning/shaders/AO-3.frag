#version 330 core
in vec4 ourColor;

out vec4 color;

void main()
{
    //color = uvec4(ourColor.r, ourColor.g, ourColor.b, 255);
    color = vec4(ourColor.r, ourColor.g, ourColor.b, ourColor.a);
    // color = vec4(1.0, 0.0, 0.0, 1.0);
    //hello
}
