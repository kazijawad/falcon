#include <falcon/core/light.h>
#include <falcon/core/renderer.h>
#include <falcon/materials/pbr_material.h>
#include <falcon/textures/image_texture.h>
#include <falcon/utils/file_utils.h>

namespace falcon {

PBRMaterial::PBRMaterial(glm::vec4 baseColor, float metallic, float roughness) :
    Material(
        FileUtils::getAssetPath("/assets/shaders/pbr/vertex.glsl"),
        FileUtils::getAssetPath("/assets/shaders/pbr/fragment.glsl")
    ),
    baseColor(baseColor),
    metallic(metallic),
    roughness(roughness) {}

PBRMaterial::PBRMaterial(std::shared_ptr<ImageTexture> baseColorMap, float metallic, float roughness) :
    Material(
        FileUtils::getAssetPath("/assets/shaders/pbr/vertex.glsl"),
        FileUtils::getAssetPath("/assets/shaders/pbr/fragment-map.glsl")
    ),
    baseColorMap(baseColorMap),
    metallic(metallic),
    roughness(roughness) {}

void PBRMaterial::use(RenderState &state) {
    Material::use(state);

    if (baseColorMap != nullptr) {
        glActiveTexture(GL_TEXTURE0);
        baseColorMap->bind();
        setInt("baseColorMap", 0);
    } else {
        setVec4("baseColor", baseColor);
    }

    setFloat("metallic", metallic);
    setFloat("roughness", roughness);
    setFloat("ao", ao);

    auto numLights = state.lights.size();
    setInt("numLights", numLights);
    for (auto i = 0; i < numLights; ++i) {
        std::shared_ptr<Light> light = state.lights[i];
        setVec3Array("lightPositions", i, light->getTranslation());
        setVec3Array("lightColors", i, light->getColor());
    }
}

}
