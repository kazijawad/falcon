#ifndef transform_h
#define transform_h

#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace poly {

class Transform {
public:
    std::vector<Transform*> children;

    glm::vec3 position = glm::vec3();
    glm::vec3 rotation = glm::vec3();
    glm::vec3 scale = glm::vec3(1.0);

    glm::mat4 localMatrix = glm::mat4();
    glm::mat4 worldMatrix = glm::mat4();

    Transform();

    void add(Transform* object);
    void remove(Transform* object);

    void updateWorldMatrix(glm::mat4 &parentWorldMatrix);
    void updateWorldMatrix();
    void updateLocalMatrix();
};

}

#endif
