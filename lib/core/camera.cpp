#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <poly/core/camera.h>
#include <poly/core/transform.h>

namespace poly {

Camera::Camera(float fov, float aspect, float near, float far) : Transform(), fov(fov), aspect(aspect), near(near), far(far) {
    updateProjectionMatrix();
}

void Camera::updateWorldMatrix() {
    Transform::updateWorldMatrix();
    viewMatrix = glm::lookAt(position, glm::vec3(0.0), up);
}

void Camera::updateProjectionMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
}

}
