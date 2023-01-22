#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <polyhedron/cameras/perspective_camera.h>

namespace polyhedron {

PerspectiveCamera::PerspectiveCamera(
    float fov,
    float aspect,
    float near,
    float far
) : Camera() {
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
    projectionMatrix = glm::perspective(
        glm::radians(state.fov),
        state.aspect,
        state.near,
        state.far
    );
}

void PerspectiveCamera::handleResize(unsigned int width, unsigned int height) {
    setAspectRatio((float)width / (float)height);
}

}
