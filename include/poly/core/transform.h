#ifndef transform_h
#define transform_h

#include <vector>
#include <memory>

#include <glm/glm.hpp>

namespace poly {

class Mesh;

class Transform {
public:
    std::vector<std::shared_ptr<Mesh>> children;

    glm::vec3 position = glm::vec3(0.0);
    glm::vec3 rotation = glm::vec3(0.0);
    glm::vec3 scale = glm::vec3(1.0);

    glm::mat4 localMatrix = glm::mat4(1.0);
    glm::mat4 worldMatrix = glm::mat4(1.0);

    Transform();

    void add(std::shared_ptr<Mesh> object);
    void remove(std::shared_ptr<Mesh> object);

    void updateWorldMatrix(glm::mat4 &parentWorldMatrix);
    void updateWorldMatrix();
    void updateLocalMatrix();
};

}

#endif
