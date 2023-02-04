#include <polyhedron/cameras/perspective_camera.h>

namespace polyhedron {

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far) : Camera() {
    state.fov = fov;
    state.aspect = aspect;
    state.near = near;
    state.far = far;
    isDirty = true;
}

float PerspectiveCamera::fov() {
    return state.fov;
}

void PerspectiveCamera::setFOV(float v) {
    state.fov = v;
    isDirty = true;
}

float PerspectiveCamera::aspectRatio() {
    return state.aspect;
}

void PerspectiveCamera::setAspectRatio(float v) {
    state.aspect = v;
    isDirty = true;
}

float PerspectiveCamera::near() {
    return state.near;
}

void PerspectiveCamera::setNear(float v) {
    state.near = v;
    isDirty = true;
}

float PerspectiveCamera::far() {
    return state.far;
}

void PerspectiveCamera::setFar(float v) {
    state.far = v;
    isDirty = true;
}

void PerspectiveCamera::updateProjectionMatrix() {
    // The perspective projection is similar to the orthographic projection in
    // that there's a scaled view volume that's transformed to the canonical
    // view volume. However, a perspective projection involves field of view (fov)
    // information that influences the shape of the view volume. It's also more
    // intuitive for the user to define the frustum in terms of fov and aspect
    // ratio instead of the view bounds. With this information, a perspective
    // divide is performed of the (x, y, z) coordinates against the homogenous
    // coordinate, w. This division can also affect depth buffer accuracy because
    // the z coordinate is divided against w. The accuracy degradation is noticeable
    // for near planes close to zero or extremely large far planes.
    projectionMatrix = glm::perspective(glm::radians(state.fov), state.aspect, state.near, state.far);
}

void PerspectiveCamera::handleResize(unsigned int width, unsigned int height) {
    setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
}

}
