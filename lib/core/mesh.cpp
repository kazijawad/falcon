#include <polyhedron/core/camera.h>
#include <polyhedron/core/geometry.h>
#include <polyhedron/core/material.h>
#include <polyhedron/core/mesh.h>

namespace polyhedron {

Mesh::Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material)
    : Transform(), geometry(geometry), material(material) {}

void Mesh::draw(std::shared_ptr<Camera> camera) {
    // TODO: Look into not recalculating both matrices each frame.
    modelViewMatrix = camera->view() * worldMatrix;
    // TODO: The normal matrix could be accurately calculated using the adjoint
    // matrix, but likely not needed for our use cases. In this format, there
    // are also optimizations that can be done depending on what local transformations
    // were applied and simplifying the transpose and inverse operations.
    normalMatrix = glm::transpose(glm::inverse(modelViewMatrix));

    material->use();

    material->setMat4("model", worldMatrix);
    material->setMat4("view", camera->view());
    material->setMat4("projection", camera->projection());

    material->setMat4("modelViewMatrix", modelViewMatrix);
    material->setMat3("normalMatrix", normalMatrix);

    material->setVec3("cameraPosition", camera->translation());

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
