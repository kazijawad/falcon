#version 330 core

struct Light {
    vec3 position;
    vec3 color;
};

uniform Light lights[16];
uniform sampler2D diffuseMap;
uniform vec3 viewPosition;

in VertexData {
    vec3 position;
    vec3 normal;
    vec2 uv;
} inData;

out vec4 fragColor;

void main() {
    vec3 color = texture(diffuseMap, inData.uv).rgb;
    vec3 normal = normalize(inData.normal);
    
    // Ambient
    vec3 ambient = 0.1 * color;
    
    // Lighting
    vec3 lighting = vec3(1.0);
    for (int i = 0; i < 16; i++) {
        // Diffuse
        vec3 lightDir = normalize(lights[i].position - inData.position);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = lights[i].color * diff * color;

        // Attenuation
        vec3 result = diffuse;
        float dist = length(inData.position - lights[i].position);
        result *= 1.0 / (dist * dist);
        lighting += result;
    }
    
    fragColor = vec4(ambient + lighting, 1.0);
}
