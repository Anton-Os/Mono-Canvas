#version 430 core

layout(location = 0) in flat uint vertexID;
layout(location = 1) in vec4 pos;

uniform uint iterCount;

layout(location = 0) out vec4 frag_out;

const float threshold = 10.0;

void main() {
    vec4 start_color = vec4(0.219f, 0.447f, 0.819f, 1.0);
    vec4 end_color = vec4(1.0f, 0.701f, 0.854f, 1.0);

    vec2 z = vec2(0, 0);
    int count = -1;
    
    for (int i = 0; i < iterCount; i++) {
        vec2 nz = vec2(0, 0);
        nz.x = z.x * z.x  - z.y * z.y + pos.x;
        nz.y = 2.0 * z.x * z.y + pos.y;
        if (length(nz) > threshold) {
            count = i;
            break;
        }
        z = nz;
    }
    
    if (count == 0) {
        frag_out = end_color;
    } else if (count == -1) {
        frag_out = vec4(0, 0, 0, 0);
    } else {
        float c = sqrt(float(count) / iterCount);
        frag_out = start_color * c + end_color * (1 - c);
    }
}