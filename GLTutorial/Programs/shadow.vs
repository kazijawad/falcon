#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpace;

out VertexData {
    vec3 position;
    vec3 normal;
    vec2 uv;
    vec4 lightSpacePosition;
} outData;

void main() {
    outData.position = vec3(model * vec4(position, 1.0));
    outData.normal = transpose(inverse(mat3(model))) * normal;
    outData.uv = uv;
    outData.lightSpacePosition = lightSpace * vec4(outData.position, 1.0);

    gl_Position = projection * view * model * vec4(position, 1.0);
}
