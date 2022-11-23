#include <memory>

#include <glm/ext/matrix_transform.hpp>
#include <poly/core/transform.h>

namespace poly {

Transform::Transform() {}

void Transform::add(Transform* object) {
    children.push_back(object);
}

void Transform::remove(Transform* object) {
    children.erase(std::remove(children.begin(), children.end(), object), children.end());
}

void Transform::updateWorldMatrix(glm::mat4 &parentWorldMatrix) {
    updateLocalMatrix();

    worldMatrix = parentWorldMatrix * localMatrix;

    for (Transform* child : children) {
        child->updateWorldMatrix(worldMatrix);
    }
}

void Transform::updateWorldMatrix() {
    updateLocalMatrix();

    worldMatrix = glm::mat4(localMatrix);

    for (Transform* child : children) {
        child->updateWorldMatrix(worldMatrix);
    }
}

void Transform::updateLocalMatrix() {
    auto T = glm::translate(glm::mat4(), position);
    auto R = glm::rotate(glm::mat4(), 0.0f, rotation);
    auto S = glm::scale(glm::mat4(), scale);
    localMatrix = T * R * S;
}

}
