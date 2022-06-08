#version 330 core

in vec2 vTexCoords;

out vec4 color;

uniform sampler2D diffuse;

void main() {
    color = texture(diffuse, vTexCoords);
}
