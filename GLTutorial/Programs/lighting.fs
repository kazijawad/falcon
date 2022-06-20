#version 330 core

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

in VertexData {
    vec2 uv;
    vec3 tangentLightPosition;
    vec3 tangentViewPosition;
    vec3 tangentPosition;
} inData;

out vec4 fragColor;

void main() {
    vec3 color = texture(diffuseMap, inData.uv).rgb;
    
    // Normal
    vec3 normal = texture(normalMap, inData.uv).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    
    // Ambient
    vec3 ambient = 0.1 * color;
    
    // Diffuse
    vec3 lightDir = normalize(inData.tangentLightPosition - inData.tangentPosition);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    
    // Specular
    vec3 viewDir = normalize(inData.tangentViewPosition - inData.tangentPosition);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.2) * spec;
    
    fragColor = vec4(ambient + diffuse + specular, 1.0);
}
