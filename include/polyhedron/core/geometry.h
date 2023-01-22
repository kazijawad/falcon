#ifndef geometry_h
#define geometry_h

#include <polyhedron/polyhedron.h>

namespace polyhedron {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

class Geometry {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Geometry();
    Geometry(std::vector<Vertex> vertices);
    Geometry(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void draw();

protected:
    unsigned int VAO, VBO, EBO;

    void bindBuffers();
};

}

#endif
