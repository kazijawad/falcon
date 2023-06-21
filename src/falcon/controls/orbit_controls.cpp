#include <algorithm>

#include <falcon/cameras/perspective_camera.h>
#include <falcon/controls/orbit_controls.h>

namespace falcon {

const int OrbitControls::ORBIT_BUTTON = GLFW_MOUSE_BUTTON_LEFT;
const int OrbitControls::ZOOM_BUTTON = GLFW_MOUSE_BUTTON_MIDDLE;
const int OrbitControls::PAN_BUTTON = GLFW_MOUSE_BUTTON_RIGHT;

OrbitControls::OrbitControls(
    RenderWindow* window,
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
    target(camera->getTarget()),
    offset(camera->getTranslation() - target) {
    spherical.radius = sphericalTarget.radius = glm::length(offset);
    spherical.theta = sphericalTarget.theta = glm::atan(offset.x, offset.z);
    spherical.phi = sphericalTarget.phi = glm::acos(std::min(std::max(offset.y / sphericalTarget.radius, -1.0f), 1.0f));

    window->getSize(&windowWidth, &windowHeight);
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
    camera->setTranslation(target + offset);
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
        window->getCursor(&x, &y);

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

void OrbitControls::handleResize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}

void OrbitControls::handleRotation(double x, double y) {
    glm::vec2 temp = (glm::vec2(x, y) - rotationStart) * rotationSpeed;

    sphericalDelta.theta -= (2.0 * PI * temp.x) / static_cast<float>(windowHeight);
    sphericalDelta.phi -= (2.0 * PI * temp.y) / static_cast<float>(windowHeight);

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
    // Calculate movement in NDC.
    glm::vec2 delta(
        (x - panStart.x) / static_cast<float>(windowWidth),
        -((y - panStart.y) / static_cast<float>(windowHeight))
    );

    // Calculate camera orientation.
    glm::mat4 view = camera->getView();
    glm::vec3 up(view[0][1], view[1][1], view[2][1]);
    glm::vec3 right(view[0][0], view[1][0], view[2][0]);
    
    // Scale by distance.
    float distance = glm::length(target - camera->getTranslation());
    panDelta += (up * delta.y + right * delta.x) * distance * panSpeed;

    // Update for next frame.
    panStart.x = x;
    panStart.y = y;
}

}
