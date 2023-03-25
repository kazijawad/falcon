#ifndef orthographic_camera_h
#define orthographic_camera_h

#include <falcon/core/camera.h>

namespace falcon {

class OrthographicCamera : public Camera {
public:
    OrthographicCamera(float left, float right, float bottom, float top, float near, float far);

    float getLeft();
    void setLeft(float v);

    float getRight();
    void setRight(float v);

    float getBottom();
    void setBottom(float v);

    float getTop();
    void setTop(float v);

    float getNear();
    void setNear(float v);

    float getFar();
    void setFar(float v);

    void updateProjection() override;

    void handleResize(unsigned int width, unsigned int height) override;

private:
    // These variables define the AABB that will be
    // transformed to the canonical view volume.
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;
};

}

#endif
