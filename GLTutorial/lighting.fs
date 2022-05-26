#version 330 core

in vec3 vNormal;
in vec3 vPosition;
in vec2 vTexCoords;

out vec4 color;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    // vec3 position;
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPosition;

void main() {
    // Ambient
    vec3 ambient = light.ambient * texture(material.diffuse, vTexCoords).rgb;
    
    // Diffuse
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, vTexCoords).rgb;
    
    // Specular
    vec3 viewDir = normalize(viewPosition - vPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, vTexCoords).rgb;
    
    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0);
}
