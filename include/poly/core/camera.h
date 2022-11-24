#ifndef camera_h
#define camera_h

#include <glm/glm.hpp>

#include <poly/core/transform.h>

namespace poly {

class Camera : public Transform {
public:
    static const glm::vec3 UP;

    glm::mat4 viewMatrix = glm::mat4();
    glm::mat4 projectionMatrix = glm::mat4();

    float fov;
    float aspect;
    float near;
    float far;

    Camera(float fov, float aspect, float near, float far);

    void updateWorldMatrix();
    void updateProjectionMatrix();

    void lookAt(glm::vec3 v);
};

}


#endif
