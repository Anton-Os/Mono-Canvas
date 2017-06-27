#version 330 core
#pragma debug(on)

layout(location = 0) in vec4 vposition;
layout(location = 1) in vec4 vcolor;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 ViewProjection;

out vec4 fcolor;

void main() {
   fcolor = vcolor;
   gl_Position = ViewProjection*vposition;
}
