#ifndef orthographic_camera_h
#define orthographic_camera_h

#include <falcon/core/camera.h>

namespace falcon {

class OrthographicCamera : public Camera {
public:
    OrthographicCamera(float left, float right, float bottom, float top, float near, float far);

    float getLeft() const;
    void setLeft(float v);

    float getRight() const;
    void setRight(float v);

    float getBottom() const;
    void setBottom(float v);

    float getTop() const;
    void setTop(float v);

    float getNear() const;
    void setNear(float v);

    float getFar() const;
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
