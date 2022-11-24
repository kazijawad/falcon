#include <vector>

#include <glad/gl.h>

#include <poly/core/geometry.h>

namespace poly {

Geometry::Geometry(std::vector<float> rawVertices) {
    std::vector<Vertex> newVertices;

    for (unsigned int i = 0; i < rawVertices.size(); i += 8) {
        float x = rawVertices[i];
        float y = rawVertices[i + 1];
        float z = rawVertices[i + 2];

        float nx = rawVertices[i + 3];
        float ny = rawVertices[i + 4];
        float nz = rawVertices[i + 5];

        float uvx = rawVertices[i + 6];
        float uvy = rawVertices[i + 7];

        Vertex vertex;
        vertex.position = glm::vec3(x, y, z);
        vertex.normal = glm::vec3(nx, ny, nz);
        vertex.uv = glm::vec2(uvx, uvy);

        newVertices.push_back(vertex);
    }

    vertices = newVertices;
    indices = std::vector<unsigned int>();

    init();
}

Geometry::Geometry(std::vector<Vertex> vertices) : Geometry(vertices, std::vector<unsigned int>()) {}
Geometry::Geometry(std::tuple<std::vector<Vertex>, std::vector<unsigned int>> vertexIndexPair) :
    Geometry(std::get<0>(vertexIndexPair), std::get<1>(vertexIndexPair)) {}

Geometry::Geometry(std::vector<Vertex> vertices, std::vector<unsigned int> indices) : vertices(vertices), indices(indices) {
    init();
}

void Geometry::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    if (!indices.empty()) {
        glGenBuffers(1, &EBO);
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    if (!indices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    }

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);

    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

    // UV
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uv));

    glBindVertexArray(0);
}

void Geometry::draw() {
    glBindVertexArray(VAO);

    if (indices.empty()) {
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    } else {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
}

}
