#ifndef point_light_h
#define point_light_h

#include <polyhedron/core/light.h>

namespace polyhedron {

class PointLight : public Light {
public:
    PointLight(glm::vec3 position, glm::vec3 color);
};

}

#endif
