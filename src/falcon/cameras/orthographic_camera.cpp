#include <falcon/cameras/orthographic_camera.h>

namespace falcon {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far) :
    Camera(),
    left(left),
    right(right),
    bottom(bottom),
    top(top),
    near(near),
    far(far) {
    needsUpdate = true;
}

float OrthographicCamera::getLeft() const {
    return left;
}

void OrthographicCamera::setLeft(float v) {
    left = v;
    needsUpdate = true;
}

float OrthographicCamera::getRight() const {
    return right;
}

void OrthographicCamera::setRight(float v) {
    right = v;
    needsUpdate = true;
}

float OrthographicCamera::getBottom() const {
    return bottom;
}

void OrthographicCamera::setBottom(float v) {
    bottom = v;
    needsUpdate = true;
}

float OrthographicCamera::getTop() const {
    return top;
}

void OrthographicCamera::setTop(float v) {
    top = v;
    needsUpdate = true;
}

float OrthographicCamera::getNear() const {
    return near;
}

void OrthographicCamera::setNear(float v) {
    near = v;
    needsUpdate = true;
}

float OrthographicCamera::getFar() const {
    return far;
}

void OrthographicCamera::setFar(float v) {
    far = v;
    needsUpdate = true;
}

void OrthographicCamera::updateProjection() {
    // The projection matrix is calculated by translating the AABB to the
    // origin. Then, it's scaled to the canonical view volume, which is a cube
    // ranging from (-1, -1, -1) to (1, 1, 1) in OpenGL. The far plane is
    // negated because the projection faces the negative z direction, but
    // it's intuitive for the user to think of the far plane as greater than
    // the near plane.
    projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
}

void OrthographicCamera::handleResize(unsigned int width, unsigned int height) {}

}
