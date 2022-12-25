#include <poly/materials/pbr_material.h>

namespace poly {

PBRMaterial::PBRMaterial(
    glm::vec4 baseColor,
    float metallic,
    float roughness
) : ShaderMaterial("./assets/shaders/pbr/vertex.glsl", "./assets/shaders/pbr/fragment.glsl"),
    baseColor(baseColor),
    metallic(metallic),
    roughness(roughness) {}

void PBRMaterial::use() {
    Material::use();

    program.setVec4("baseColor", baseColor);
    program.setFloat("metallic", metallic);
    program.setFloat("roughness", roughness);
    program.setFloat("ao", ao);
}

}
