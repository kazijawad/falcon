#include <algorithm>

#include <polyhedron/cameras/perspective_camera.h>
#include <polyhedron/controls/orbit_controls.h>

namespace polyhedron {

const int OrbitControls::ORBIT_BUTTON = GLFW_MOUSE_BUTTON_LEFT;
const int OrbitControls::ZOOM_BUTTON = GLFW_MOUSE_BUTTON_MIDDLE;
const int OrbitControls::PAN_BUTTON = GLFW_MOUSE_BUTTON_RIGHT;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    static_cast<OrbitControls*>(glfwGetWindowUserPointer(window))->handleMouseButton(button, action);
}

void cursorPosCallback(GLFWwindow* window, double x, double y) {
    static_cast<OrbitControls*>(glfwGetWindowUserPointer(window))->handleMouseMove(x, y);
}

OrbitControls::OrbitControls(
    GLFWwindow* window,
    std::shared_ptr<Camera> camera,
    float ease,
    float inertia,
    float rotationSpeed,
    float zoomSpeed,
    float panSpeed,
    float minPolarAngle,
    float maxPolarAngle,
    float minAzimuthAngle,
    float maxAzimuthAngle,
    float minDistance,
    float maxDistance
) :
    window(window),
    camera(camera),
    ease(ease),
    inertia(inertia),
    rotationSpeed(rotationSpeed),
    zoomSpeed(zoomSpeed),
    panSpeed(panSpeed),
    minPolarAngle(minPolarAngle),
    maxPolarAngle(maxPolarAngle),
    minAzimuthAngle(minAzimuthAngle),
    maxAzimuthAngle(maxAzimuthAngle),
    minDistance(minDistance),
    maxDistance(maxDistance),
    target(camera->target()) {
    offset = glm::vec3(camera->translation()) - target;

    spherical.radius = sphericalTarget.radius = glm::length(offset);
    spherical.theta = sphericalTarget.theta = glm::atan(offset.x, offset.z);
    spherical.phi = sphericalTarget.phi = glm::acos(std::min(std::max(offset.y / sphericalTarget.radius, -1.0f), 1.0f));

    // Setup event handlers.
    glfwSetWindowUserPointer(window, this);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
}

float OrbitControls::zoomScale() {
    return std::powf(0.95, zoomSpeed);
}

void OrbitControls::update() {
    // Apply delta.
    sphericalTarget.radius *= sphericalDelta.radius;
    sphericalTarget.theta += sphericalDelta.theta;
    sphericalTarget.phi += sphericalDelta.phi;

    // Apply boundaries.
    sphericalTarget.radius = std::max(minDistance, std::min(maxDistance, sphericalTarget.radius));
    sphericalTarget.theta = std::max(minAzimuthAngle, std::min(maxAzimuthAngle, sphericalTarget.theta));
    sphericalTarget.phi = std::max(minPolarAngle, std::min(maxPolarAngle, sphericalTarget.phi));

    // Ease values.
    spherical.radius += (sphericalTarget.radius - spherical.radius) * ease;
    spherical.theta += (sphericalTarget.theta - spherical.theta) * ease;
    spherical.phi += (sphericalTarget.phi - spherical.phi) * ease;

    // Apply pan to target. This is necessary because the offset shits and
    // it's relative to the target.
    target += panDelta;

    // Apply rotation to offset.
    float sinPhiRadius = spherical.radius * std::sin(std::max(0.000001f, spherical.phi));
    offset.x = sinPhiRadius * std::sin(spherical.theta);
    offset.y = spherical.radius * std::cos(spherical.phi);
    offset.z = sinPhiRadius * std::cos(spherical.theta);

    // Update camera positioning.
    camera->applyTranslation(target + offset);
    camera->lookAt(target);

    // Apply inertia to spherical coordinates.
    sphericalDelta.theta *= inertia;
    sphericalDelta.phi *= inertia;
    panDelta *= inertia;

    // Reset scale every frame to avoid applying scale multiple times.
    sphericalDelta.radius = 1.0;
}

void OrbitControls::handleMouseButton(int button, int action) {
    if (action == GLFW_PRESS) {
        // Get current cursor position.
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        if (button == OrbitControls::ORBIT_BUTTON) {
            state = OrbitState::ROTATE;
            rotationStart.x = x;
            rotationStart.y = y;
        } else if (button == OrbitControls::ZOOM_BUTTON) {
            state = OrbitState::DOLLY;
            dollyStart.x = x;
            dollyStart.y = y;
        } else if (button == OrbitControls::PAN_BUTTON) {
            state = OrbitState::PAN;
            panStart.x = x;
            panStart.y = y;
        }
    } else {
        state = OrbitState::NONE;
    }
}

void OrbitControls::handleMouseMove(double x, double y) {
    if (state == OrbitState::NONE) return;

    if (state == OrbitState::ROTATE) {
        handleRotation(x, y);
    } else if (state == OrbitState::DOLLY) {
        handleDolly(x, y);
    } else if (state == OrbitState::PAN) {
        handlePan(x, y);
    }
}

void OrbitControls::handleRotation(double x, double y) {
    // TODO: Improve?
    int height;
    glfwGetFramebufferSize(window, NULL, &height);

    glm::vec2 temp = (glm::vec2(x, y) - rotationStart) * rotationSpeed;
    sphericalDelta.theta -= (2.0 * PI * temp.x) / height;
    sphericalDelta.phi -= (2.0 * PI * temp.y) / height;

    rotationStart.x = x;
    rotationStart.y = y;
}

void OrbitControls::handleDolly(double x, double y) {
    glm::vec2 temp = (glm::vec2(x, y) - dollyStart);

    if (temp.y > 0) {
        sphericalDelta.radius /= zoomScale();
    } else if (temp.y < 0) {
        sphericalDelta.radius /= (1.0f / zoomScale());
    }

    dollyStart.x = x;
    dollyStart.y = y;
}

void OrbitControls::handlePan(double x, double y) {
    // TODO: Improve?
    int height;
    glfwGetFramebufferSize(window, NULL, &height);

    glm::vec2 delta = (glm::vec2(x, y) - panStart) * panSpeed;
    auto distance = (camera->translation() - target).length();
    auto localTransform = camera->localSpace();

    // Set standard FOV.
    float fov = 45.0;
    if (std::shared_ptr<PerspectiveCamera> perspective = std::dynamic_pointer_cast<PerspectiveCamera>(camera)) {
        fov = perspective->fov();
    }
    distance *= std::tan(((fov / 2.0) * PI) / 180.0);

    // Pan horizontally.
    float offset = (2.0f * delta.x * distance) / height;
    panDelta += glm::vec3(localTransform[0][0], localTransform[0][1], localTransform[0][2]) * -offset;

    // Pan vertically.
    offset = (2.0f * delta.y * distance) / height;
    panDelta += glm::vec3(localTransform[1][0], localTransform[1][1], localTransform[2][2]) * offset;

    panStart.x = x;
    panStart.y = y;
}

}
