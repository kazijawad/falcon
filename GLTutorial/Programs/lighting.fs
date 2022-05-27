#version 330 core

#define NUM_POINT_LIGHTS 4

in vec3 vNormal;
in vec3 vPosition;
in vec2 vTexCoords;

out vec4 color;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    
    float cutoff;
    float outerCutoff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;

uniform DirLight dirLight;
uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform vec3 viewPosition;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 pos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 pos, vec3 viewDir);

void main() {
    // Properties
    vec3 norm = normalize(vNormal);
    vec3 viewDir = normalize(viewPosition - vPosition);
    
    // Directional Light
    vec3 result = calcDirLight(dirLight, norm, viewDir);
    
    // Point Lights
    for (int i = 0; i < NUM_POINT_LIGHTS; i++) {
        result += calcPointLight(pointLights[i], norm, vPosition, viewDir);
    }
    
    // Spot Light
    result += calcSpotLight(spotLight, norm, vPosition, viewDir);
    
    color = vec4(result, 1.0);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Combine
    vec3 ambient = light.ambient * texture(material.diffuse, vTexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, vTexCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.specular, vTexCoords).rgb;
    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 pos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - pos);
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Attenuation
    float distance = length(light.position - pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Combine
    vec3 ambient = light.ambient * texture(material.diffuse, vTexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, vTexCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.specular, vTexCoords).rgb;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return ambient + diffuse + specular;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 pos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - pos);
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Attenuation
    float distance = length(light.position - pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
    // Combine
    vec3 ambient = light.ambient * texture(material.diffuse, vTexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, vTexCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.specular, vTexCoords).rgb;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return ambient + diffuse + specular;
}
