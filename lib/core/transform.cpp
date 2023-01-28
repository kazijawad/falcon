#include <algorithm>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <polyhedron/core/transform.h>

namespace polyhedron {

Transform::Transform() {
    updateLocalMatrix();
    worldMatrix = glm::mat4(localMatrix);
}

void Transform::addChild(std::shared_ptr<Transform> object) {
    children.push_back(object);
}

void Transform::removeChild(std::shared_ptr<Transform> object) {
    children.erase(std::remove(children.begin(), children.end(), object), children.end());
}

glm::mat4 Transform::localSpace() {
    return localMatrix;
}

void Transform::setLocalSpace(glm::mat4 matrix) {
    localMatrix = matrix;
}

glm::mat4 Transform::worldSpace() {
    return worldMatrix;
}

void Transform::setWorldSpace(glm::mat4 matrix) {
    worldMatrix = matrix;
}

glm::vec3 Transform::translation() {
    return t;
}

void Transform::applyTranslation(float x, float y, float z) {
    t.x = x;
    t.y = y;
    t.z = z;
    isDirty = true;
}

void Transform::applyTranslation(glm::vec3 position) {
    t.x = position.x;
    t.y = position.y;
    t.z = position.z;
    isDirty = true;
}

glm::quat Transform::rotation() {
    return r;
}

void Transform::applyRotation(float angle, glm::vec3 axis) {
    r.x = axis.x;
    r.y = axis.y;
    r.z = axis.z;
    r.w = angle;
    isDirty = true;
}

glm::vec3 Transform::scale() {
    return s;
}

void Transform::applyScale(float x, float y, float z) {
    s.x = x;
    s.y = y;
    s.z = z;
    isDirty = true;
}

void Transform::updateWorldMatrix(glm::mat4* parentWorldMatrix) {
    if (isDirty) {
        updateLocalMatrix();
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
        child->updateWorldMatrix(&worldMatrix);
    }
}

void Transform::updateLocalMatrix() {
    // A local matrix on a mesh, or collection of meshes, can be defined by
    // three common properties of translation, rotation, and scale. The order
    // of matrix products is important because matrix products are not commutative,
    // but they are associative. For example, it could be fruitful in calculating
    // the translation and rotation matrix together in certain scenarios.
    auto T = glm::translate(t);
    auto R = glm::mat4_cast(r);
    auto S = glm::scale(s);
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
