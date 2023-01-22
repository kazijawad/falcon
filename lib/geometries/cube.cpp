#include <polyhedron/geometries/cube.h>
#include <polyhedron/geometries/plane.h>

namespace polyhedron {

Cube::Cube(
    int width,
    int height,
    int depth,
    unsigned int widthSegments,
    unsigned int heightSegments,
    unsigned int depthSegments
) :
    Geometry() {
    unsigned int numVertices = (widthSegments + 1) * (heightSegments + 1) * 2 +
        (widthSegments + 1) * (depthSegments + 1) * 2 + (heightSegments + 1) * (depthSegments + 1) * 2;
    unsigned int numIndices =
        (widthSegments * heightSegments * 2 + widthSegments * depthSegments * 2 + heightSegments * depthSegments * 2) *
        6;

    vertices.reserve(numVertices);
    indices.resize(numIndices);

    std::vector<float> position(numVertices * 3);
    std::vector<float> normal(numVertices * 3);
    std::vector<float> uv(numVertices * 2);

    unsigned int i = 0;
    unsigned int ii = 0;

    // Right Plane
    Plane::build(
        position, normal, uv, indices, depth, height, width, depthSegments, heightSegments, 2, 1, 0, -1.0f, -1.0f, i, ii
    );
    i += (depthSegments + 1) * (heightSegments + 1);
    ii += depthSegments * heightSegments;

    // Left Plane
    Plane::build(
        position, normal, uv, indices, depth, height, -width, depthSegments, heightSegments, 2, 1, 0, 1.0f, -1.0f, i, ii
    );
    i += (depthSegments + 1) * (heightSegments + 1);
    ii += depthSegments * heightSegments;

    // Top Plane
    Plane::build(
        position, normal, uv, indices, width, depth, height, depthSegments, widthSegments, 0, 2, 1, 1.0f, 1.0f, i, ii
    );
    i += (widthSegments + 1) * (depthSegments + 1);
    ii += widthSegments * depthSegments;

    // Bottom Plane
    Plane::build(
        position, normal, uv, indices, width, depth, -height, depthSegments, widthSegments, 0, 2, 1, 1.0f, -1.0f, i, ii
    );
    i += (widthSegments + 1) * (depthSegments + 1);
    ii += widthSegments * depthSegments;

    // Back Plane
    Plane::build(
        position,
        normal,
        uv,
        indices,
        width,
        height,
        -depth,
        widthSegments,
        heightSegments,
        0,
        1,
        2,
        -1.0f,
        -1.0f,
        i,
        ii
    );
    i += (widthSegments + 1) * (heightSegments + 1);
    ii += widthSegments * heightSegments;

    // Front Plane
    Plane::build(
        position, normal, uv, indices, width, height, depth, widthSegments, heightSegments, 0, 1, 2, 1.0f, -1.0f, i, ii
    );

    for (auto i = 0; i < numVertices; i++) {
        Vertex vertex;

        vertex.position = glm::vec3(position[i * 3], position[i * 3 + 1], position[i * 3 + 2]);

        vertex.normal = glm::vec3(normal[i * 3], normal[i * 3 + 1], normal[i * 3 + 2]);

        vertex.uv = glm::vec2(uv[i * 2], uv[i * 2 + 1]);

        vertices.push_back(vertex);
    }

    bindBuffers();
}

}
