#ifndef mesh_h
#define mesh_h

#include <polyhedron/core/transform.h>
#include <polyhedron/polyhedron.h>

namespace polyhedron {

class Mesh : public Transform {
public:
    std::shared_ptr<Geometry> geometry;
    std::shared_ptr<Material> material;

    glm::mat4 modelViewMatrix = glm::mat4();
    glm::mat3 normalMatrix = glm::mat3();

    Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material);

    void draw(RenderState &state);
};

}

#endif
