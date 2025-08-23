#version 430 core

out vec4 FragColor;

uniform sampler2D computeImage;

in vec2 TexCoord; // Pass this from your vertex shader

void main() {
    FragColor = texture(computeImage, TexCoord);
}