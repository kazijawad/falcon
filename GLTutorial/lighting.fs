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
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPosition;

void main() {
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(light.position - vPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 viewDir = normalize(viewPosition - vPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    // Lighting
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, vTexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, vTexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, vTexCoords));
    
    color = vec4(ambient + diffuse + specular, 1.0);
}
