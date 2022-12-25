#version 330 core

#define PI 3.14159265359

uniform vec3 cameraPosition;

uniform vec4 baseColor;
uniform float metallic;
uniform float roughness;
uniform float ao;

in vec3 vPosition;
in vec3 vNormal;

out vec4 fragColor;

// TODO: Replace with proper lighting setup.
// For testing purposes.
const vec3 lightPositions[4] = vec3[](
    vec3(-5.0,  5.0, 5.0),
    vec3( 5.0,  5.0, 5.0),
    vec3(-5.0, -5.0, 5.0),
    vec3( 5.0, -5.0, 5.0)
);

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float numerator = a2;

    float denominator = (NdotH2 * (a2 - 1.0) + 1.0);
    denominator = PI * denominator * denominator;

    return numerator / denominator;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;

    float denominator = NdotV * (1.0 - k) + k;

    return NdotV / denominator;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    return GeometrySchlickGGX(NdotV, roughness) * GeometrySchlickGGX(NdotL, roughness);
}

vec3 fresnelSchlick(float cosTheta, vec3 FO) {
    return FO + (1.0 - FO) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main() {
    vec3 N = normalize(vNormal);
    vec3 V = normalize(cameraPosition - vPosition);

    // Calculate reflectance at normal incidence.
    vec3 FO = vec3(0.04);
    FO = mix(FO, baseColor.rgb, metallic);

    // Reflectance Equation (Render Equation)
    vec3 Lo = vec3(0.0);
    for (int i = 0; i < 4; i++) {
        vec3 lightPosition = lightPositions[i];
        vec3 lightColor = vec3(300.0);

        // Calcualte per-light radiance.
        vec3 L = normalize(lightPosition - vPosition);
        vec3 H = normalize(V + L);
        float distance = length(lightPosition - vPosition);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColor * attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);
        float G = GeometrySmith(N, V, L, roughness);
        vec3 F = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), FO);

        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular = numerator / denominator;

        vec3 kSpecular = F;
        // The refracted light represents the diffused light.
        // We can calculate the diffuse shading from the inverse
        // of the specular shading because the microfacet model
        // relies on energy conservation.
        vec3 kDiffuse = vec3(1.0) - kSpecular;
        // Multiplying by the inverse of the metallic
        // factor causes pure metals to have no diffuse
        // lighting.
        kDiffuse *= 1.0 - metallic;

        float NdotL = max(dot(N, L), 0.0);

        Lo += (kDiffuse * baseColor.rgb / PI + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.03) * baseColor.rgb * ao;
    vec3 color = ambient + Lo;

    // HDR Tone Mapping
    color = color / (color + vec3(1.0));

    // Gamma Correction
    color = pow(color, vec3(1.0 / 2.2));

    fragColor = vec4(color, baseColor.a);
}
