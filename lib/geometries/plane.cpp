#include <poly/geometries/plane.h>

namespace poly {

Plane::Plane() : Plane(1, 1, 1, 1) {}
Plane::Plane(unsigned int width, unsigned int height) : Plane(width, height, 1, 1) {}

Plane::Plane(unsigned int width, unsigned int height, unsigned int widthSegments, unsigned int heightSegments) :
    Geometry(Plane::build(width, height, widthSegments, heightSegments)) {}

std::tuple<std::vector<Vertex>, std::vector<unsigned int>> Plane::build(
    unsigned int width,
    unsigned int height,
    unsigned int widthSegments,
    unsigned int heightSegments
) {
    return Plane::build(width, height, 0, widthSegments, heightSegments, 1.0f, -1.0f, 0, 0);
}

std::tuple<std::vector<Vertex>, std::vector<unsigned int>> Plane::build(
    unsigned int width,
    unsigned int height,
    unsigned int depth,
    unsigned int widthSegments,
    unsigned int heightSegments,
    float uDirection,
    float vDirection,
    unsigned int i,
    unsigned int ii
) {
    unsigned int numVertices = (widthSegments + 1) * (heightSegments + 1);
    unsigned int numIndices = widthSegments * heightSegments * 6;

    std::vector<Vertex> newVertices(numVertices);
    std::vector<unsigned int> newIndices(numIndices);

    unsigned int io = i;
    float segmentedWidth = (float) width / widthSegments;
    float segmentedHeight = (float) height / heightSegments;

    for (unsigned int iy = 0; iy <= heightSegments; iy++) {
        float y = iy * segmentedHeight - height / 2.0f;

        for (unsigned int ix = 0; ix <= widthSegments; ix++, i++) {
            float x = ix * segmentedWidth - width / 2.0f;

            Vertex vertex;
            vertex.position = glm::vec3(0.0f);
            vertex.position.x = x * uDirection;
            vertex.position.y = y * vDirection;
            vertex.position.z = depth / 2.0f;

            vertex.normal = glm::vec3(0.0f);
            vertex.normal.x = 0.0f;
            vertex.normal.y = 0.0f;
            vertex.normal.z = depth >= 0.0f ? 1.0f : -1.0f;

            vertex.uv = glm::vec2(0.0f);
            vertex.uv.x = (float) ix / widthSegments;
            vertex.uv.y = 1.0f - (float) iy / heightSegments;

            newVertices[i] = vertex;
            if (iy == heightSegments || ix == widthSegments) continue;

            unsigned int a = io + ix + iy * (widthSegments + 1);
            unsigned int b = io + ix + (iy + 1) * (widthSegments + 1);
            unsigned int c = io + ix + (iy + 1) * (widthSegments + 1) + 1;
            unsigned int d = io + ix + iy * (widthSegments + 1) + 1;

            newIndices[ii * 6] = a;
            newIndices[ii * 6 + 1] = b;
            newIndices[ii * 6 + 2] = d;
            newIndices[ii * 6 + 3] = b;
            newIndices[ii * 6 + 4] = c;
            newIndices[ii * 6 + 5] = d;

            ii++;
        }
    }

    return std::make_tuple(newVertices, newIndices);
}

}
