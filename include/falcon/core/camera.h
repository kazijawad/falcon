#ifndef camera_h
#define camera_h

#include <falcon/core/transform.h>

namespace falcon {

class Camera : public Transform {
public:
    static const glm::vec3 UP;

    Camera();
    virtual ~Camera() = default;

    glm::vec3 getTarget();
    void lookAt(glm::vec3 v);

    glm::mat4 getView();
    void updateView();

    glm::mat4 getProjection();
    virtual void updateProjection() = 0;

    void updateWorld(glm::mat4* parentWorldMatrix = nullptr) override;

    virtual void handleResize(unsigned int width, unsigned int height) = 0;

protected:
    glm::mat4 viewMatrix = glm::mat4();
    glm::mat4 projectionMatrix = glm::mat4();

private:
    glm::vec3 target;
};

}

#endif
