#include <falcon/materials/normal_material.h>
#include <falcon/utils/file_utils.h>

namespace falcon {

NormalMaterial::NormalMaterial()
    : Material(
        FileUtils::getAssetPath("/assets/shaders/normal/vertex.glsl"),
        FileUtils::getAssetPath("/assets/shaders/normal/fragment.glsl")
    ) {}

}
