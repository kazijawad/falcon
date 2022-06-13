#version 330 core

uniform sampler2D diffuseMap;
uniform sampler2D shadowMap;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

in VertexData {
    vec3 position;
    vec3 normal;
    vec2 uv;
    vec4 lightSpacePosition;
} inData;

out vec4 fragColor;

float calculateShadow(vec4 lightSpacePosition, float bias) {
    // Perspective Divide, i.e. clip-space to NDC
    vec3 projectedCoords = lightSpacePosition.xyz / lightSpacePosition.w;

    // [-1, 1] to [0, 1]
    projectedCoords = projectedCoords * 0.5 + 0.5;
    if (projectedCoords.z > 1.0) {
        return 0.0;
    }
    
    float currentDepth = projectedCoords.z;
    
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projectedCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }

    shadow /= 9.0;

    return shadow;
}

void main() {
    vec3 color = texture(diffuseMap, inData.uv).rgb;
    vec3 normal = normalize(inData.normal);
    vec3 lightColor = vec3(1.0);
    
    // Ambient
    vec3 ambient = 0.15 * lightColor;
    
    // Diffuse
    vec3 lightDir = normalize(lightPosition - inData.position);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    vec3 viewDir = normalize(viewPosition - inData.position);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;
    
    // Shadow
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    float shadow = calculateShadow(inData.lightSpacePosition, bias);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    
    fragColor = vec4(lighting, 1.0);
}
