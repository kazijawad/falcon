#include <polyhedron/core/camera.h>
#include <polyhedron/core/geometry.h>
#include <polyhedron/core/material.h>
#include <polyhedron/core/mesh.h>
#include <polyhedron/core/renderer.h>

namespace polyhedron {

Mesh::Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material) :
    Transform(),
    geometry(geometry),
    material(material) {}

void Mesh::draw(RenderState &state) {
    // TODO: Look into not recalculating both matrices each frame.
    modelViewMatrix = state.camera->getView() * worldMatrix;
    // TODO: The normal matrix could be accurately calculated using the adjoint
    // matrix, but likely not needed for our use cases. In this format, there
    // are also optimizations that can be done depending on what local transformations
    // were applied and simplifying the transpose and inverse operations.
    normalMatrix = glm::transpose(glm::inverse(modelViewMatrix));

    material->use(state);

    material->setMat4("model", worldMatrix);
    material->setMat4("view", state.camera->getView());
    material->setMat4("projection", state.camera->getProjection());

    material->setMat4("modelViewMatrix", modelViewMatrix);
    material->setMat3("normalMatrix", normalMatrix);

    material->setVec3("cameraPosition", state.camera->getTranslation());

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
