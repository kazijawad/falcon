#ifndef geometry_h
#define geometry_h

#include <vector>
#include <tuple>

#include <glm/glm.hpp>

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

    Geometry(std::vector<float> vertices);
    Geometry(std::vector<Vertex> vertices);
    Geometry(std::tuple<std::vector<Vertex>, std::vector<unsigned int>> vertexIndexPair);
    Geometry(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void draw();

private:
    unsigned int VAO, VBO, EBO;

    void init();
};

}

#endif
