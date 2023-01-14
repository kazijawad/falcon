#include <polyhedron/materials/pbr_material.h>
#include <polyhedron/utils/file_utils.h>

namespace polyhedron {

PBRMaterial::PBRMaterial(
    glm::vec4 baseColor,
    float metallic,
    float roughness
) : Material(
        FileUtils::getAssetPath("/assets/shaders/pbr/vertex.glsl"),
        FileUtils::getAssetPath("/assets/shaders/pbr/fragment.glsl")
    ),
    baseColor(baseColor),
    metallic(metallic),
    roughness(roughness) {}

void PBRMaterial::use() {
    Material::use();

    setVec4("baseColor", baseColor);
    setFloat("metallic", metallic);
    setFloat("roughness", roughness);
    setFloat("ao", ao);
}

}
