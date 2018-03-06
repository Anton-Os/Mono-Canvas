#version 440 core

uniform uint renderMode;

layout(location = 0) out vec4 frag_out;

void main(){
    if(renderMode == 1){
        frag_out = vec4(0.0, 1.0, 1.0, 1.0);
    } else {
        frag_out = vec4(0.0, 0.0, 0.0, 1.0);
    }
}