#include <falcon/lights/directional_light.h>

namespace falcon {

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color) : Light(color), direction(direction) {}

glm::vec3 DirectionalLight::getDirection() const {
    return direction;
}

void DirectionalLight::setDirection(glm::vec3 v) {
    direction = v;
    needsUpdate = true;
}

}
