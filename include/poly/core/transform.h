#ifndef transform_h
#define transform_h

#include <vector>
#include <memory>

#include <glm/glm.hpp>

namespace poly {

class Mesh;
class Camera;

class Transform {
public:
    std::vector<std::shared_ptr<Transform>> children;

    glm::vec3 position = glm::vec3(0.0);
    glm::vec3 rotation = glm::vec3(0.0);
    glm::vec3 scale = glm::vec3(1.0);

    glm::mat4 localMatrix = glm::mat4(1.0);
    glm::mat4 worldMatrix = glm::mat4(1.0);

    Transform();

    void add(std::shared_ptr<Transform> object);
    void remove(std::shared_ptr<Transform> object);

    virtual void updateWorldMatrix(glm::mat4 &parentWorldMatrix);
    virtual void updateWorldMatrix();
    virtual void updateLocalMatrix();

    void traverse(std::shared_ptr<Camera> camera);
};

}

#endif
