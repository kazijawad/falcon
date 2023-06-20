#ifndef orbit_controls_h
#define orbit_controls_h

#include <limits>

#include <falcon/falcon.h>

namespace falcon {

struct SphericalCoordinate {
    float radius;
    float phi;
    float theta;
};

enum OrbitState {
    NONE,
    ROTATE,
    DOLLY,
    PAN,
};

class OrbitControls {
public:
    static const int ORBIT_BUTTON;
    static const int ZOOM_BUTTON;
    static const int PAN_BUTTON;

    float ease;
    float inertia;

    float rotationSpeed;
    float zoomSpeed;
    float panSpeed;

    float minPolarAngle;
    float maxPolarAngle;

    float minAzimuthAngle;
    float maxAzimuthAngle;

    float minDistance;
    float maxDistance;

    OrbitControls(
        GLFWwindow* window,
        std::shared_ptr<Camera> camera,
        float ease = 0.25,
        float inertia = 0.85,
        float rotationSpeed = 0.1,
        float zoomSpeed = 0.5,
        float panSpeed = 0.25,
        float minPolarAngle = 0.0,
        float maxPolarAngle = PI,
        float minAzimuthAngle = -std::numeric_limits<float>::infinity(),
        float maxAzimuthAngle = std::numeric_limits<float>::infinity(),
        float minDistance = 0,
        float maxDistance = std::numeric_limits<float>::infinity()
    );

    float zoomScale();

    void update();

    void handleMouseButton(int button, int action);
    void handleMouseMove(double x, double y);
    void handleResize(int width, int height);

private:
    GLFWwindow* window;
    std::shared_ptr<Camera> camera;

    int windowWidth = 0;
    int windowHeight = 0;

    SphericalCoordinate spherical = {1, 0, 0};
    SphericalCoordinate sphericalDelta = {1, 0, 0};
    SphericalCoordinate sphericalTarget = {1, 0, 0};

    glm::vec3 target = glm::vec3(0.0);
    glm::vec3 offset = glm::vec3(0.0);
    glm::vec3 panDelta = glm::vec3(0.0);

    OrbitState state = OrbitState::NONE;

    glm::vec2 rotationStart = glm::vec2(0.0);
    glm::vec2 dollyStart = glm::vec2(0.0);
    glm::vec2 panStart = glm::vec2(0.0);

    void handleRotation(double x, double y);
    void handleDolly(double x, double y);
    void handlePan(double x, double y);
};

}

#endif
