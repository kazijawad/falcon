#include <memory>
#include <iostream>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <poly/core/transform.h>
#include <poly/core/mesh.h>

namespace poly {

Transform::Transform() {}

void Transform::add(std::shared_ptr<Mesh> object) {
    children.push_back(object);
}

void Transform::remove(std::shared_ptr<Mesh> object) {
    children.erase(std::remove(children.begin(), children.end(), object), children.end());
}

void Transform::updateWorldMatrix(glm::mat4 &parentWorldMatrix) {
    updateLocalMatrix();

    worldMatrix = parentWorldMatrix * localMatrix;

    for (std::shared_ptr<Mesh> child : children) {
        child->updateWorldMatrix(worldMatrix);
    }
}

void Transform::updateWorldMatrix() {
    updateLocalMatrix();

    worldMatrix = glm::mat4(localMatrix);

    for (std::shared_ptr<Mesh> child : children) {
        child->updateWorldMatrix(worldMatrix);
    }
}

void Transform::updateLocalMatrix() {
    auto T = glm::translate(glm::mat4(1.0), position);
    auto R = glm::eulerAngleXYX(rotation.x, rotation.y, rotation.z);
    auto S = glm::scale(glm::mat4(1.0), scale);
    localMatrix = T * R * S;
}

}
