#include <glm/gtc/matrix_inverse.hpp>

#include <poly/core/mesh.h>

namespace poly {

Mesh::Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material) : Transform(), geometry(geometry), material(material) {}

void Mesh::draw(std::shared_ptr<Camera> camera) {
    modelViewMatrix = camera->viewMatrix * worldMatrix;
    normalMatrix = glm::transpose(glm::inverse(modelViewMatrix));

    auto program = material->program;
    program.use();

    program.setMat4("model", worldMatrix);
    program.setMat4("view", camera->viewMatrix);
    program.setMat4("projection", camera->projectionMatrix);

    program.setMat4("modelViewMatrix", modelViewMatrix);
    program.setMat3("normalMatrix", normalMatrix);

    geometry->draw();
}

}
