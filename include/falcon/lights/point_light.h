#ifndef point_light_h
#define point_light_h

#include <falcon/core/light.h>

namespace falcon {

class PointLight : public Light {
public:
    PointLight(glm::vec3 position, glm::vec3 color);
};

}

#endif
