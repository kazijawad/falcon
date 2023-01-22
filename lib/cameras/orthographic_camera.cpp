#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <polyhedron/cameras/orthographic_camera.h>

namespace polyhedron {

OrthographicCamera::OrthographicCamera(
    float left,
    float right,
    float bottom,
    float top,
    float near,
    float far
) : Camera() {
    // These state variables define the AABB that will be
    // transformed to the canonical view volume.
    state.left = left;
    state.right = right;
    state.bottom = bottom;
    state.top = top;
    state.near = near;
    state.far = far;
    isDirty = true;
}

float OrthographicCamera::left() {
    return state.left;
}

void OrthographicCamera::setLeft(float v) {
    state.left = v;
    isDirty = true;
}

float OrthographicCamera::right() {
    return state.right;
}

void OrthographicCamera::setRight(float v) {
    state.right = v;
    isDirty = true;
}

float OrthographicCamera::bottom() {
    return state.bottom;
}

void OrthographicCamera::setBottom(float v) {
    state.bottom = v;
    isDirty = true;
}

float OrthographicCamera::top() {
    return state.top;
}

void OrthographicCamera::setTop(float v) {
    state.top = v;
    isDirty = true;
}

float OrthographicCamera::near() {
    return state.near;
}

void OrthographicCamera::setNear(float v) {
    state.near = v;
    isDirty = true;
}

float OrthographicCamera::far() {
    return state.far;
}

void OrthographicCamera::setFar(float v) {
    state.far = v;
    isDirty = true;
}

void OrthographicCamera::updateProjectionMatrix() {
    // The projection matrix is calculated by translating the AABB to the
    // origin. Then, it's scaled to the canonical view volume, which is a cube
    // ranging from (-1, -1, -1) to (1, 1, 1) in OpenGL. The far plane is
    // negated because the projection faces the negative z direction, but
    // it's intuitive for the user to think of the far plane as greater than
    // the near plane.
    projectionMatrix = glm::ortho(
        state.left,
        state.right,
        state.bottom,
        state.top,
        state.near,
        state.far
    );
}

void OrthographicCamera::handleResize(unsigned int width, unsigned int height) {}

}
