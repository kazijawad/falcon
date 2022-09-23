#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 vWorldPosition;
out vec3 vNormal;
out vec2 vUv;

void main() {
    vWorldPosition = vec3(model * vec4(position, 1.0));
    vNormal = mat3(model) * normal;
    vUv = uv;

    gl_Position = projection * view * vec4(vWorldPosition, 1.0);
}
