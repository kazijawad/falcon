#ifndef directional_light_h
#define directional_light_h

#include <polyhedron/core/light.h>

namespace polyhedron {

class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3 direction, glm::vec3 color);

    glm::vec3 getDirection();
    void setDirection(glm::vec3 v);

private:
    glm::vec3 direction;
};

}

#endif
