#version 330 core

uniform sampler2D hdrBuffer;
uniform float exposure;

in vec2 vUv;

out vec4 fragColor;

const float gamma = 2.2;

void main() {
    vec3 hdrColor = texture(hdrBuffer, vUv).rgb;
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    result = pow(result, vec3(1.0 / gamma));
    fragColor = vec4(result, 1.0);
}
