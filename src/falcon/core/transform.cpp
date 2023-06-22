#include <algorithm>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include <falcon/core/transform.h>

namespace falcon {

Transform::Transform() {
    updateLocal();
    worldMatrix = glm::mat4(localMatrix);
}

void Transform::addChild(std::shared_ptr<Transform> child) {
    children.push_back(child);
}

void Transform::removeChild(std::shared_ptr<Transform> child) {
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

glm::mat4 Transform::getLocal() const {
    return localMatrix;
}

void Transform::setLocal(glm::mat4 mat) {
    localMatrix = mat;
}

glm::mat4 Transform::getWorld() const {
    return worldMatrix;
}

void Transform::setWorld(glm::mat4 mat) {
    worldMatrix = mat;
}

glm::vec3 Transform::getTranslation() const {
    return translation;
}

void Transform::setTranslation(float x, float y, float z) {
    translation.x = x;
    translation.y = y;
    translation.z = z;
    needsUpdate = true;
}

void Transform::setTranslation(glm::vec3 v) {
    translation.x = v.x;
    translation.y = v.y;
    translation.z = v.z;
    needsUpdate = true;
}

glm::quat Transform::getRotation() const {
    return rotation;
}

void Transform::setRotation(float angle, glm::vec3 axis) {
    rotation.x = axis.x;
    rotation.y = axis.y;
    rotation.z = axis.z;
    rotation.w = angle;
    needsUpdate = true;
}

glm::vec3 Transform::getScale() const {
    return scale;
}

void Transform::setScale(float x, float y, float z) {
    scale.x = x;
    scale.y = y;
    scale.z = z;
    needsUpdate = true;
}

void Transform::setScale(glm::vec3 v) {
    scale.x = v.x;
    scale.y = v.y;
    scale.z = v.z;
    needsUpdate = true;
}

void Transform::updateWorld(Transform* parentTransform) {
    if (needsUpdate) {
        updateLocal();
    }

    // When updating the world transformation, we need to multiply the local
    // transformation against its parent. If there is no parent defined it's
    // assumed the object's local transformation is in world space. This can
    // be beneficial in creating complex scenes because children objects are
    // only dependent on their parent transformation. A classic example is
    // creating a solar system where the moon only orbits the Earth, which
    // orbits the Sun.
    if (parentTransform != nullptr && parentTransform->needsUpdate) {
        worldMatrix = parentTransform->getWorld() * localMatrix;
    }

    for (std::shared_ptr<Transform> child : children) {
        child->updateWorld(this);
    }

    needsUpdate = false;
}

void Transform::updateLocal() {
    // A local matrix on a mesh, or collection of meshes, can be defined by
    // three common properties of translation, rotation, and scale. The order
    // of matrix products is important because matrix products are not commutative,
    // but they are associative. For example, it could be fruitful in calculating
    // the translation and rotation matrix together in certain scenarios.
    auto T = glm::translate(translation);
    auto R = glm::mat4_cast(rotation);
    auto S = glm::scale(scale);
    localMatrix = T * R * S;
}

void Transform::traverse(std::function<bool(std::shared_ptr<Transform>)> fn) {
    // Exit early if returned true.
    if (fn(this->shared_from_this())) return;

    for (std::shared_ptr<Transform> child : children) {
        child->traverse(fn);
    }
}

}
