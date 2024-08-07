#ifndef camera_h
#define camera_h

#include <falcon/core/transform.h>

namespace falcon {

class Camera : public Transform {
public:
    static const glm::vec3 UP;

    Camera() : Transform() {};
    virtual ~Camera() = default;

    glm::vec3 getTarget() const;
    void lookAt(glm::vec3 point);

    glm::mat4 getView() const;
    void updateView();

    glm::mat4 getProjection() const;
    virtual void updateProjection() = 0;

    void updateWorld(Transform* parentTransform = nullptr) override;

    virtual void handleResize(unsigned int width, unsigned int height) = 0;

protected:
    glm::mat4 viewMatrix = glm::mat4();
    glm::mat4 projectionMatrix = glm::mat4();

private:
    glm::vec3 target = glm::vec3(0.0f);
};

}

#endif
