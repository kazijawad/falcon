#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vUv;

void main() {
    vPosition = vec3(model * vec4(position, 1.0));
    vNormal = mat3(model) * normal;
    vUv = uv;

    gl_Position = projection * view * model * vec4(position, 1.0);
}
