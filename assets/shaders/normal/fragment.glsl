#version 330 core

in vec3 vNormal;

out vec4 fragColor;

void main() {
    fragColor = vec4(vNormal, 1.0);
}
