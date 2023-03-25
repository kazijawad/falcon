#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 vNormal;

void main() {
    vNormal = normalMatrix * normal;
    gl_Position = projection * view * model * vec4(position, 1.0);
}
