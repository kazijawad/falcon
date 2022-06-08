#version 330 core

in vec2 vTexCoords;

out vec4 color;

uniform sampler2D screenTexture;

void main() {
    color = vec4(texture(screenTexture, vTexCoords).rgb, 1.0);
}
