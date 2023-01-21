#ifndef camera_h
#define camera_h

#include <glm/glm.hpp>

#include <polyhedron/core/transform.h>

namespace polyhedron {

class Camera : public Transform {
public:
    static glm::vec3 UP;

    Camera(float fov, float aspect, float near, float far);

    glm::mat4 view();
    glm::mat4 projection();

    void setFOV(float v);
    void setAspectRatio(float v);
    void setNearPlane(float v);
    void setFarPlane(float v);

    void updateWorldMatrix();
    void updateProjectionMatrix();

    void lookAt(glm::vec3 target);

protected:
    float fov;
    float aspect;
    float near;
    float far;

    glm::vec3 target = glm::vec3(0.0);

    glm::mat4 viewMatrix = glm::mat4();
    glm::mat4 projectionMatrix = glm::mat4();
};

}


#endif
