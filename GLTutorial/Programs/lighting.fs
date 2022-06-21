#version 330 core

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform float heightScale;

in VertexData {
    vec2 uv;
    vec3 tangentLightPosition;
    vec3 tangentViewPosition;
    vec3 tangentPosition;
} inData;

out vec4 fragColor;

vec2 parallaxMapping(vec2 uv, vec3 viewDir) {
    const float minLayers = 8.0;
    const float maxLayers = 32.0;
    float numLayers = mix(maxLayers, minLayers, max(dot(vec3(0.0, 0.0, 1.0), viewDir), 0.0));
    
    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;
    
    // Amount to shift UVs per layer from P
    vec2 P = viewDir.xy * heightScale;
    vec2 deltaUVs = P / numLayers;
    
    vec2 currentUVs = uv;
    float currentDepth = texture(depthMap, currentUVs).r;
    while (currentLayerDepth < currentDepth) {
        currentUVs -= deltaUVs;
        currentDepth = texture(depthMap, currentUVs).r;
        currentLayerDepth += layerDepth;
    }
    
    return currentUVs;
}

void main() {
    // Offset UVs with Parallax Mapping
    vec3 viewDir = normalize(inData.tangentViewPosition - inData.tangentPosition);
    vec2 uv = parallaxMapping(inData.uv, viewDir);
    if (uv.x > 1.0 || uv.y > 1.0 || uv.x < 0.0 || uv.y < 0.0) discard;
    
    // Diffuse
    vec3 color = texture(diffuseMap, uv).rgb;
    
    // Normal
    vec3 normal = texture(normalMap, uv).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    
    // Ambient
    vec3 ambient = 0.1 * color;
    
    // Diffuse
    vec3 lightDir = normalize(inData.tangentLightPosition - inData.tangentPosition);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    
    // Specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.2) * spec;
    
    fragColor = vec4(ambient + diffuse + specular, 1.0);
}
