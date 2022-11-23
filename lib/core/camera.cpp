#include "glm/ext/matrix_clip_space.hpp"
#include <vector>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <poly/core/camera.h>

namespace poly {

Camera::Camera(float fov, float aspect, float near, float far) : Transform(), fov(fov), aspect(aspect), near(near), far(far) {
    updateProjectionMatrix();
}

void Camera::updateProjectionMatrix() {
    projectionMatrix = glm::perspective(fov, aspect, near, far);
}

}
