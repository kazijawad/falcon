#include <algorithm>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <poly/core/transform.h>
#include <poly/core/mesh.h>

namespace poly {

Transform::Transform() {}

void Transform::add(std::shared_ptr<Transform> object) {
    children.push_back(object);
}

void Transform::remove(std::shared_ptr<Transform> object) {
    children.erase(std::remove(children.begin(), children.end(), object), children.end());
}

void Transform::updateWorldMatrix(glm::mat4 &parentWorldMatrix) {
    updateLocalMatrix();

    worldMatrix = parentWorldMatrix * localMatrix;

    for (std::shared_ptr<Transform> child : children) {
        child->updateWorldMatrix(worldMatrix);
    }
}

void Transform::updateWorldMatrix() {
    updateLocalMatrix();

    worldMatrix = glm::mat4(localMatrix);

    for (std::shared_ptr<Transform> child : children) {
        child->updateWorldMatrix(worldMatrix);
    }
}

void Transform::updateLocalMatrix() {
    auto T = glm::translate(position);
    auto R = glm::toMat4(rotation);
    auto S = glm::scale(scale);
    localMatrix = T * R * S;
}

void Transform::traverse(std::shared_ptr<Camera> camera) {
    for (auto child : children) {
        if (std::dynamic_pointer_cast<Mesh>(child) != nullptr) {
            auto mesh = std::dynamic_pointer_cast<Mesh>(child);
            mesh->draw(camera);
        }
        child->traverse(camera);
    }
}

}
