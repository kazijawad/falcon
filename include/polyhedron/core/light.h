#ifndef light_h
#define light_h

#include <polyhedron/core/transform.h>

namespace polyhedron {

class Light : public Transform {
public:
    Light(glm::vec3 color);
    virtual ~Light() = default;

    glm::vec3 getColor();
    void setColor(glm::vec3 v);

protected:
    glm::vec3 color;
};

}

#endif
