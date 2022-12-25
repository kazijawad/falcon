#include <poly/materials/normal_material.h>

namespace poly {

NormalMaterial::NormalMaterial()
    : ShaderMaterial("./assets/shaders/normal/vertex.glsl", "./assets/shaders/normal/fragment.glsl") {}

}
