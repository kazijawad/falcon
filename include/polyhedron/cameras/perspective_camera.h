#ifndef perspective_camera_h
#define perspective_camera_h

#include <glm/glm.hpp>

#include <polyhedron/core/camera.h>

namespace polyhedron {

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(float fov, float aspect, float near, float far);

    float fov();
    void setFOV(float v);

    float aspectRatio();
    void setAspectRatio(float v);

    float near();
    void setNear(float v);

    float far();
    void setFar(float v);

    void updateProjectionMatrix() override;

    void handleResize(unsigned int width, unsigned int height) override;

private:
    struct CameraState {
        float fov;
        float aspect;
        float near;
        float far;
    } state;
};

}


#endif
