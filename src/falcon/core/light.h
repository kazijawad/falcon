#ifndef light_h
#define light_h

#include <falcon/core/transform.h>

namespace falcon {

class Light : public Transform {
public:
    Light(glm::vec3 color);
    virtual ~Light() = default;

    glm::vec3 getColor() const;
    void setColor(glm::vec3 v);

protected:
    glm::vec3 color;
};

}

#endif
