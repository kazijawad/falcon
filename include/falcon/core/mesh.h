#ifndef mesh_h
#define mesh_h

#include <falcon/core/transform.h>
#include <falcon/falcon.h>

namespace falcon {

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
