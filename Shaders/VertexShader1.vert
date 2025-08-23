#version 430 core

layout(location = 0) in vec2 position;// in space [-1, 1]

out vec2 TexCoord;// in space [0,1]

void main() {
    TexCoord = position * 0.5 + 0.5;
    gl_Position = vec4(position, 0.0, 1.0);
}