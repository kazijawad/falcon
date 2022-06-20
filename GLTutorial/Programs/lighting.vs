#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

out VertexData {
    vec2 uv;
    vec3 tangentLightPosition;
    vec3 tangentViewPosition;
    vec3 tangentPosition;
} outData;

void main() {
    outData.uv = uv;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 N = normalize(normalMatrix * normal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);

    mat3 TBN = transpose(mat3(T, B, N));
    outData.tangentLightPosition = TBN * lightPosition;
    outData.tangentViewPosition = TBN * viewPosition;
    outData.tangentPosition = TBN * vec3(model * vec4(position, 1.0));

    gl_Position = projection * view * model * vec4(position, 1.0);
}
