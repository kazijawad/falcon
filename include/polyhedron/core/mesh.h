#ifndef mesh_h
#define mesh_h

#include <memory>

#include <glm/glm.hpp>

#include <polyhedron/core/transform.h>
#include <polyhedron/core/geometry.h>
#include <polyhedron/core/material.h>
#include <polyhedron/core/camera.h>

namespace polyhedron {

class Mesh : public Transform {
public:
    std::shared_ptr<Geometry> geometry;
    std::shared_ptr<Material> material;

    glm::mat4 modelViewMatrix = glm::mat4();
    glm::mat3 normalMatrix = glm::mat3();

    Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material);

    void draw(std::shared_ptr<Camera> camera);
};

}

#endif
