#include <glm/gtc/matrix_inverse.hpp>

#include <poly/core/mesh.h>

namespace poly {

Mesh::Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material) : Transform(), geometry(geometry), material(material) {}

void Mesh::draw(std::shared_ptr<Camera> camera) {
    modelViewMatrix = camera->viewMatrix * worldMatrix;
    normalMatrix = glm::transpose(glm::inverse(modelViewMatrix));

    material->use();

    material->program.setMat4("model", worldMatrix);
    material->program.setMat4("view", camera->viewMatrix);
    material->program.setMat4("projection", camera->projectionMatrix);

    material->program.setMat4("modelViewMatrix", modelViewMatrix);
    material->program.setMat3("normalMatrix", normalMatrix);

    material->program.setVec3("cameraPosition", camera->position);

    geometry->draw();
}

}
