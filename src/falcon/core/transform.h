#ifndef transform_h
#define transform_h

#include <falcon/falcon.h>

namespace falcon {

class Transform : public std::enable_shared_from_this<Transform> {
public:
    bool isVisible = true;

    std::vector<std::shared_ptr<Transform>> children;

    Transform();
    virtual ~Transform() {}

    void addChild(std::shared_ptr<Transform> child);
    void removeChild(std::shared_ptr<Transform> child);

    glm::mat4 getLocal();
    void setLocal(glm::mat4 mat);

    glm::mat4 getWorld();
    void setWorld(glm::mat4 mat);

    glm::vec3 getTranslation();
    void setTranslation(float x, float y, float z);
    void setTranslation(glm::vec3 translation);

    glm::quat getRotation();
    void setRotation(float angle, glm::vec3 axis);

    glm::vec3 getScale();
    void setScale(float x, float y, float z);
    void setScale(glm::vec3 scale);

    virtual void updateWorld(glm::mat4* parentWorldMatrix = nullptr);
    void updateLocal();

    void traverse(std::function<bool(std::shared_ptr<Transform>)> fn);

protected:
    bool isDirty = false;

    glm::mat4 worldMatrix;
    glm::mat4 localMatrix;

    glm::vec3 translation = glm::vec3(0.0);
    // The quaternion can be define as (v, w) where v is a 3-component
    // vector with imaginary components and w is a scalar. The 3-component
    // vector defines the axis of rotation and w defines the angle in
    // radians. We use a quaternion instead of euler angles for rotation
    // to avoid gimbal lock in rotation transformations. In the future,
    // it might be nice to expose methods that convert between the two
    // because euler angles are generally easier to work with for the user.
    glm::quat rotation = glm::quat();
    glm::vec3 scale = glm::vec3(1.0);
};

}

#endif
