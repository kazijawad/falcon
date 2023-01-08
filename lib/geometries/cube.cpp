#include <polyhedron/geometries/cube.h>

namespace polyhedron {

Cube::Cube() : Cube(1, 1, 1, 1, 1, 1) {}
Cube::Cube(int width, int height, int depth) : Cube(width, height, depth, 1, 1, 1) {}

Cube::Cube(
    int width,
    int height,
    int depth,
    unsigned int widthSegments,
    unsigned int heightSegments,
    unsigned int depthSegments
) : Geometry(Cube::build(width, height, depth, widthSegments, heightSegments, depthSegments)) {}

std::tuple<std::vector<Vertex>, std::vector<unsigned int>> Cube::build(
    int width,
    int height,
    int depth,
    unsigned int widthSegments,
    unsigned int heightSegments,
    unsigned int depthSegments
) {
    unsigned int numVertices = (widthSegments + 1) * (heightSegments + 1) * 2 +
        (widthSegments + 1) * (depthSegments + 1) * 2 +
        (heightSegments + 1) * (depthSegments + 1) * 2;
    unsigned int numIndices = (widthSegments * heightSegments * 2 +
        widthSegments * depthSegments * 2 +
        heightSegments * depthSegments * 2) * 6;

    std::vector<Vertex> newVertices(numVertices);

    std::vector<float> position(numVertices * 3);
    std::vector<float> normal(numVertices * 3);
    std::vector<float> uv(numVertices * 2);
    std::vector<unsigned int> index(numIndices);

    unsigned int i = 0;
    unsigned int ii = 0;

    // Right Plane
    Plane::build(
        position,
        normal,
        uv,
        index,
        depth,
        height,
        width,
        depthSegments,
        heightSegments,
        2,
        1,
        0,
        -1.0f,
        -1.0f,
        i,
        ii
    );
    i += (depthSegments + 1) * (heightSegments + 1);
    ii += depthSegments * heightSegments;

    // Left Plane
    Plane::build(
        position,
        normal,
        uv,
        index,
        depth,
        height,
        -width,
        depthSegments,
        heightSegments,
        2,
        1,
        0,
        1.0f,
        -1.0f,
        i,
        ii
    );
    i += (depthSegments + 1) * (heightSegments + 1);
    ii += depthSegments * heightSegments;

    // Top Plane
    Plane::build(
        position,
        normal,
        uv,
        index,
        width,
        depth,
        height,
        depthSegments,
        widthSegments,
        0,
        2,
        1,
        1.0f,
        1.0f,
        i,
        ii
    );
    i += (widthSegments + 1) * (depthSegments + 1);
    ii += widthSegments * depthSegments;

    // Bottom Plane
    Plane::build(
        position,
        normal,
        uv,
        index,
        width,
        depth,
        -height,
        depthSegments,
        widthSegments,
        0,
        2,
        1,
        1.0f,
        -1.0f,
        i,
        ii
    );
    i += (widthSegments + 1) * (depthSegments + 1);
    ii += widthSegments * depthSegments;

    // Back Plane
    Plane::build(
        position,
        normal,
        uv,
        index,
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
        position,
        normal,
        uv,
        index,
        width,
        height,
        depth,
        widthSegments,
        heightSegments,
        0,
        1,
        2,
        1.0f,
        -1.0f,
        i,
        ii
    );

    for (unsigned int i = 0; i < newVertices.size(); i++) {
        Vertex vertex;

        vertex.position = glm::vec3(
            position[i * 3],
            position[i * 3 + 1],
            position[i * 3 + 2]
        );

        vertex.normal = glm::vec3(
            normal[i * 3],
            normal[i * 3 + 1],
            normal[i * 3 + 2]
        );

        vertex.uv = glm::vec2(
            uv[i * 2],
            uv[i * 2 + 1]
        );

        newVertices[i] = vertex;
    }

    return std::make_tuple(newVertices, index);
}

}
