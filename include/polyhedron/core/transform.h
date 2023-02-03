#ifndef transform_h
#define transform_h

#include <polyhedron/polyhedron.h>

namespace polyhedron {

class Transform : public std::enable_shared_from_this<Transform> {
public:
    bool isVisible = true;

    std::vector<std::shared_ptr<Transform>> children;

    Transform();

    virtual ~Transform() = default;

    void addChild(std::shared_ptr<Transform> object);
    void removeChild(std::shared_ptr<Transform> object);

    glm::mat4 localSpace();
    void setLocalSpace(glm::mat4 matrix);

    glm::mat4 worldSpace();
    void setWorldSpace(glm::mat4 matrix);

    glm::vec3 translation();
    void applyTranslation(float x, float y, float z);
    void applyTranslation(glm::vec3 position);

    glm::quat rotation();
    void applyRotation(float angle, glm::vec3 axis);

    glm::vec3 scale();
    void applyScale(float x, float y, float z);

    virtual void updateWorldMatrix(glm::mat4* parentWorldMatrix = nullptr);
    void updateLocalMatrix();

    void traverse(std::function<bool(std::shared_ptr<Transform>)> fn);

protected:
    bool isDirty = false;

    glm::mat4 worldMatrix;
    glm::mat4 localMatrix;

    glm::vec3 t = glm::vec3(0.0);
    // The quaternion can be define as (v, w) where v is a 3-component
    // vector with imaginary components and w is a scalar. The 3-component
    // vector defines the axis of rotation and w defines the angle in
    // radians. We use a quaternion instead of euler angles for rotation
    // to avoid gimbal lock in rotation transformations. In the future,
    // it might be nice to expose methods that convert between the two
    // because euler angles are generally easier to work with for the user.
    glm::quat r = glm::quat();
    glm::vec3 s = glm::vec3(1.0);
};

}

#endif
