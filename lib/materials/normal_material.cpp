#include <poly/materials/normal_material.h>
#include <poly/utils/file_utils.h>

namespace poly {

NormalMaterial::NormalMaterial()
    : ShaderMaterial(
        FileUtils::getAssetPath("/assets/shaders/normal/vertex.glsl"),
        FileUtils::getAssetPath("/assets/shaders/normal/fragment.glsl")
    ) {}

}
