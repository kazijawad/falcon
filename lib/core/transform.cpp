#include <algorithm>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include <polyhedron/core/transform.h>

namespace polyhedron {

Transform::Transform() {
    updateLocal();
    worldMatrix = glm::mat4(localMatrix);
}

void Transform::addChild(std::shared_ptr<Transform> object) {
    children.push_back(object);
}

void Transform::removeChild(std::shared_ptr<Transform> object) {
    children.erase(std::remove(children.begin(), children.end(), object), children.end());
}

glm::mat4 Transform::getLocal() {
    return localMatrix;
}

void Transform::setLocal(glm::mat4 v) {
    localMatrix = v;
}

glm::mat4 Transform::getWorld() {
    return worldMatrix;
}

void Transform::setWorld(glm::mat4 v) {
    worldMatrix = v;
}

glm::vec3 Transform::getTranslation() {
    return translation;
}

void Transform::setTranslation(float x, float y, float z) {
    translation.x = x;
    translation.y = y;
    translation.z = z;
    isDirty = true;
}

void Transform::setTranslation(glm::vec3 v) {
    translation.x = v.x;
    translation.y = v.y;
    translation.z = v.z;
    isDirty = true;
}

glm::quat Transform::getRotation() {
    return rotation;
}

void Transform::setRotation(float angle, glm::vec3 axis) {
    rotation.x = axis.x;
    rotation.y = axis.y;
    rotation.z = axis.z;
    rotation.w = angle;
    isDirty = true;
}

glm::vec3 Transform::getScale() {
    return scale;
}

void Transform::setScale(float x, float y, float z) {
    scale.x = x;
    scale.y = y;
    scale.z = z;
    isDirty = true;
}

void Transform::setScale(glm::vec3 v) {
    scale.x = v.x;
    scale.y = v.y;
    scale.z = v.z;
    isDirty = true;
}

void Transform::updateWorld(glm::mat4* parentWorldMatrix) {
    if (isDirty) {
        updateLocal();
        isDirty = false;
    }

    // TODO: Improve this by not recalculating every frame.
    // A potential solution is to update the parameter to be the parent
    // transform and check against its dirty flag.
    //
    // When updating the world transformation, we need to multiply the local
    // transformation against its parent. If there is no parent defined it's
    // assumed the object's local transformation is in world space. This can
    // be beneficial in creating complex scenes because children objects are
    // only dependent on their parent transformation. A classic example is
    // creating a solar system where the moon only orbits the Earth, which
    // orbits the Sun.
    if (parentWorldMatrix != nullptr) {
        worldMatrix = (*parentWorldMatrix) * localMatrix;
    } else {
        worldMatrix = glm::mat4(localMatrix);
    }

    for (std::shared_ptr<Transform> child : children) {
        child->updateWorld(&worldMatrix);
    }
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
