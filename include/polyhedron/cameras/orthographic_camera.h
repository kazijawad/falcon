#ifndef orthographic_camera_h
#define orthographic_camera_h

#include <polyhedron/core/camera.h>

namespace polyhedron {

class OrthographicCamera : public Camera {
public:
    OrthographicCamera(float left, float right, float bottom, float top, float near, float far);

    float left();
    void setLeft(float v);

    float right();
    void setRight(float v);

    float bottom();
    void setBottom(float v);

    float top();
    void setTop(float v);

    float near();
    void setNear(float v);

    float far();
    void setFar(float v);

    void updateProjectionMatrix() override;

    void handleResize(unsigned int width, unsigned int height) override;

private:
    struct CameraState {
        float left;
        float right;
        float bottom;
        float top;
        float near;
        float far;
    } state;
};

}

#endif
