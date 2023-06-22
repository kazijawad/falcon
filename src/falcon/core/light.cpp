#include <falcon/core/light.h>

namespace falcon {

Light::Light(glm::vec3 color) : color(color) {}

glm::vec3 Light::getColor() const {
    return color;
}

void Light::setColor(glm::vec3 v) {
    color = v;
    needsUpdate = true;
}

}
