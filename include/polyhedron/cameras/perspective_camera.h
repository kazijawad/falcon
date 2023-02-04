#ifndef perspective_camera_h
#define perspective_camera_h

#include <polyhedron/core/camera.h>

namespace polyhedron {

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(float fov, float aspect, float near, float far);

    float getFOV();
    void setFOV(float v);

    float getAspectRatio();
    void setAspectRatio(float v);

    float getNear();
    void setNear(float v);

    float getFar();
    void setFar(float v);

    void updateProjection() override;

    void handleResize(unsigned int width, unsigned int height) override;

private:
    float fov;
    float aspect;
    float near;
    float far;
};

}

#endif
