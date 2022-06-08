#version 330 core

in vec3 vPosition;
in vec3 vNormal;

out vec4 color;

uniform vec3 cameraPosition;
uniform samplerCube skybox;

void main() {
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(vPosition - cameraPosition);
    vec3 R = refract(I, normalize(vNormal), ratio);
    color = vec4(texture(skybox, R).rgb, 1.0);
}
