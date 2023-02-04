#include <polyhedron/core/light.h>
#include <polyhedron/core/renderer.h>
#include <polyhedron/materials/pbr_material.h>
#include <polyhedron/utils/file_utils.h>

namespace polyhedron {

PBRMaterial::PBRMaterial(glm::vec4 baseColor, float metallic, float roughness) :
    Material(
        FileUtils::getAssetPath("/assets/shaders/pbr/vertex.glsl"),
        FileUtils::getAssetPath("/assets/shaders/pbr/fragment.glsl")
    ),
    baseColor(baseColor),
    metallic(metallic),
    roughness(roughness) {}

void PBRMaterial::use(RenderState &state) {
    Material::use(state);

    setVec4("baseColor", baseColor);
    setFloat("metallic", metallic);
    setFloat("roughness", roughness);
    setFloat("ao", ao);

    auto numLights = state.lights.size();
    setInt("numLights", numLights);
    for (auto i = 0; i < numLights; ++i) {
        std::shared_ptr<Light> light = state.lights[i];
        setVec3("lightPositions[" + std::to_string(i) + "]", light->getTranslation());
        setVec3("lightColors[" + std::to_string(i) + "]", light->getColor());
    }
}

}
