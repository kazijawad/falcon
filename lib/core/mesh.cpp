#include <glad/gl.h>
#include <glm/gtc/matrix_inverse.hpp>

#include <polyhedron/core/mesh.h>

namespace polyhedron {

Mesh::Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material) : Transform(), geometry(geometry), material(material) {}

void Mesh::draw(std::shared_ptr<Camera> camera) {
    modelViewMatrix = camera->viewMatrix * worldMatrix;
    normalMatrix = glm::transpose(glm::inverse(modelViewMatrix));

    material->use();

    material->setMat4("model", worldMatrix);
    material->setMat4("view", camera->viewMatrix);
    material->setMat4("projection", camera->projectionMatrix);

    material->setMat4("modelViewMatrix", modelViewMatrix);
    material->setMat3("normalMatrix", normalMatrix);

    material->setVec3("cameraPosition", camera->position);

    if (material->depthTest) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    if (material->depthWrite) {
        glDepthMask(GL_TRUE);
    } else {
        glDepthMask(GL_FALSE);
    }

    geometry->draw();
}

}
