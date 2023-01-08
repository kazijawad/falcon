#include <polyhedron/materials/normal_material.h>
#include <polyhedron/utils/file_utils.h>

namespace polyhedron {

NormalMaterial::NormalMaterial()
    : ShaderMaterial(
        FileUtils::getAssetPath("/assets/shaders/normal/vertex.glsl"),
        FileUtils::getAssetPath("/assets/shaders/normal/fragment.glsl")
    ) {}

}
