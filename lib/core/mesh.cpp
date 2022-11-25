#include <glm/gtc/matrix_inverse.hpp>

#include <poly/core/mesh.h>

namespace poly {

Mesh::Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Program> program) : Transform(), geometry(geometry), program(program) {}

void Mesh::draw(std::shared_ptr<Camera> camera) {
    modelViewMatrix = camera->viewMatrix * worldMatrix;
    normalMatrix = glm::transpose(glm::inverse(modelViewMatrix));

    program->use();

    program->setMat4("model", worldMatrix);
    program->setMat4("view", camera->viewMatrix);
    program->setMat4("projection", camera->projectionMatrix);

    program->setMat4("modelViewMatrix", modelViewMatrix);
    program->setMat3("normalMatrix", normalMatrix);

    geometry->draw();
}

}
