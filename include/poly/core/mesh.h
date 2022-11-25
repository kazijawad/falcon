#ifndef mesh_h
#define mesh_h

#include <memory>

#include <glm/glm.hpp>

#include <poly/core/transform.h>
#include <poly/core/geometry.h>
#include <poly/core/program.h>
#include <poly/core/camera.h>

namespace poly {

class Mesh : public Transform {
public:
    std::shared_ptr<Geometry> geometry;
    std::shared_ptr<Program> program;

    glm::mat4 modelViewMatrix = glm::mat4();
    glm::mat3 normalMatrix = glm::mat3();

    Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Program> program);

    void draw(std::shared_ptr<Camera> camera);
};

}

#endif
