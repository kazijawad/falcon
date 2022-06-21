#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VertexData {
    vec3 position;
    vec3 normal;
    vec2 uv;
} outData;

void main() {
    outData.position = vec3(model * vec4(position, 1.0));
    outData.uv = uv;
    
    vec3 n = -normal;
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    outData.normal = normalize(normalMatrix * n);

    gl_Position = projection * view * model * vec4(position, 1.0);
}
