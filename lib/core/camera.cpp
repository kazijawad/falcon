#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <polyhedron/core/camera.h>
#include <polyhedron/core/transform.h>

namespace polyhedron {

glm::vec3 Camera::UP = glm::vec3(0.0, 1.0, 0.0);

Camera::Camera(float fov, float aspect, float near, float far) : Transform(), fov(fov), aspect(aspect), near(near), far(far) {
    updateProjectionMatrix();
}

glm::mat4 Camera::view() {
    return viewMatrix;
}

glm::mat4 Camera::projection() {
    return projectionMatrix;
}

void Camera::setFOV(float v) {
    fov = v;
    updateProjectionMatrix();
}

void Camera::setAspectRatio(float v) {
    aspect = v;
    updateProjectionMatrix();
}

void Camera::setNearPlane(float v) {
    near = v;
    updateProjectionMatrix();
}

void Camera::setFarPlane(float v) {
    far = v;
    updateProjectionMatrix();
}

void Camera::updateWorldMatrix() {
    Transform::updateWorldMatrix(nullptr);
    viewMatrix = glm::lookAt(t, target, Camera::UP);
}

void Camera::updateProjectionMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::lookAt(glm::vec3 target) {
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
    viewMatrix = glm::lookAt(t, target, Camera::UP);
    target = target;
}

}
