#ifndef camera_h
#define camera_h

#include <glm/glm.hpp>

#include <poly/core/transform.h>

namespace poly {

class Camera : public Transform {
public:
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 target = glm::vec3(0.0);
    glm::mat4 viewMatrix = glm::mat4();
    glm::mat4 projectionMatrix = glm::mat4();

    float fov;
    float aspect;
    float near;
    float far;

    Camera(float fov, float aspect, float near, float far);

    void updateWorldMatrix() override;
    void updateProjectionMatrix();

    void lookAt(glm::vec3 target);
};

}


#endif
