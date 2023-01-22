#ifndef camera_h
#define camera_h

#include <glm/glm.hpp>

#include <polyhedron/core/transform.h>

namespace polyhedron {

class Camera : public Transform {
public:
    static glm::vec3 UP;

    Camera();

    glm::mat4 view();
    void updateViewMatrix();

    glm::mat4 projection();
    virtual void updateProjectionMatrix() = 0;

    void updateWorldMatrix(glm::mat4* parentWorldMatrix = nullptr) override;

    void lookAt(glm::vec3 target);

    virtual void handleResize(unsigned int width, unsigned int height) = 0;

protected:
    glm::vec3 target = glm::vec3(0.0);

    glm::mat4 viewMatrix = glm::mat4();
    glm::mat4 projectionMatrix = glm::mat4();
};

}

#endif
