#include <polyhedron/lights/point_light.h>

namespace polyhedron {

PointLight::PointLight(glm::vec3 position, glm::vec3 color) : Light(color) {
    applyTranslation(position);
}

}
