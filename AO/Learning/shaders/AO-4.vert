#version 330 core
#pragma debug(on)

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

uniform mat4 ViewProjection;

out vec4 ourColor;

void main() {
    vec4 upX = vec4(0.2, 0.0, 0.0, 0.0);
    vec4 upY = vec4(0.0, 0.2, 0.0, 0.0);
    vec4 increase = vec4(0.1f, 0.1f, 0.1f, 0.0f);

    ourColor = color;
    gl_Position = ViewProjection * vec4(position.x, position.y, position.z, 1.0f);
}
