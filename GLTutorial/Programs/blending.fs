#version 330 core

in vec2 vTexCoords;

out vec4 color;

uniform sampler2D texture1;

void main() {
    vec4 texColor = texture(texture1, vTexCoords);
    if (texColor.a < 0.1) discard;
    color = texColor;
}
