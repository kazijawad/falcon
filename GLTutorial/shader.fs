#version 330 core

out vec4 color;

in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D uImage;
uniform sampler2D uMask;

void main() {
    color = mix(texture(uImage, vTexCoord), texture(uMask, vTexCoord), 0.2);
}
