#include <polyhedron/lights/directional_light.h>

namespace polyhedron {

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color) : Light(color), direction(direction) {}

glm::vec3 DirectionalLight::getDirection() {
    return direction;
}

void DirectionalLight::setDirection(glm::vec3 v) {
    direction = v;
    isDirty = true;
}

}
