#include <falcon/lights/point_light.h>

namespace falcon {

PointLight::PointLight(glm::vec3 position, glm::vec3 color) : Light(color) {
    setTranslation(position);
}

}
