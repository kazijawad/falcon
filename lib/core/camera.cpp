#include <glm/gtx/matrix_decompose.hpp>

#include <polyhedron/core/camera.h>

namespace polyhedron {

glm::vec3 Camera::UP = glm::vec3(0.0, 1.0, 0.0);

Camera::Camera() : Transform() {}

glm::vec3 Camera::target() {
    return state.target;
}

void Camera::lookAt(glm::vec3 target) {
    state.target = target;
    isDirty = true;
}

glm::mat4 Camera::view() {
    return viewMatrix;
}

void Camera::updateViewMatrix() {
    // Camera orientation is based on a transformation of the view matrix.
    // We can define a target position, a { r, u, v } basis to orient the
    // camera, and a world space up direction. The transformation matrix
    // can be define as the product of the change of basis matrix against
    // a translation matrix. The translation matrix positions the camera
    // at the origin. From the origin, we can calculate the v vector from
    // the target position to the origin. The cross product of the v vector
    // against the up direction will give us the r vector. For validation,
    // we calculate u as the cross product of r and v to ensure the correct
    // up direction.
    viewMatrix = glm::lookAt(t, state.target, Camera::UP);
}

glm::mat4 Camera::projection() {
    return projectionMatrix;
}

void Camera::updateWorldMatrix(glm::mat4* parentWorldMatrix) {
    if (isDirty) {
        updateViewMatrix();
        updateProjectionMatrix();
    }

    Transform::updateWorldMatrix(parentWorldMatrix);
}

}
