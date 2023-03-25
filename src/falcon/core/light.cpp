#include <falcon/core/light.h>

namespace falcon {

Light::Light(glm::vec3 color) : color(color) {}

glm::vec3 Light::getColor() {
    return color;
}

void Light::setColor(glm::vec3 v) {
    color = v;
    isDirty = true;
}

}
