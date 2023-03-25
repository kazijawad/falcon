#include <falcon/geometries/plane.h>

namespace falcon {

Plane::Plane(int width, int height, unsigned int widthSegments, unsigned int heightSegments) : Geometry() {
    int depth = 0;

    unsigned int u = 0;
    unsigned int v = 1;
    unsigned int w = 2;

    float uDirection = 1.0f;
    float vDirection = -1.0f;

    unsigned int i = 0;
    unsigned int ii = 0;

    unsigned int numVertices = (widthSegments + 1) * (heightSegments + 1);
    unsigned int numIndices = widthSegments * heightSegments * 6;

    vertices.reserve(numVertices);
    indices.resize(numIndices);

    unsigned int io = i;
    float segmentedWidth = static_cast<float>(width) / static_cast<float>(widthSegments);
    float segmentedHeight = static_cast<float>(height) / static_cast<float>(heightSegments);

    std::vector<float> position(numVertices * 3);
    std::vector<float> normal(numVertices * 3);
    std::vector<float> uv(numVertices * 2);

    Plane::build(
        position,
        normal,
        uv,
        indices,
        width,
        height,
        depth,
        widthSegments,
        heightSegments,
        u,
        v,
        w,
        uDirection,
        vDirection,
        i,
        ii
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

void Plane::build(
    std::vector<float> &position,
    std::vector<float> &normal,
    std::vector<float> &uv,
    std::vector<unsigned int> &index,
    int width,
    int height,
    int depth,
    unsigned int widthSegments,
    unsigned int heightSegments,
    unsigned int u,
    unsigned int v,
    unsigned int w,
    float uDirection,
    float vDirection,
    unsigned int i,
    unsigned int ii
) {
    unsigned int io = i;
    float segmentedWidth = static_cast<float>(width) / static_cast<float>(widthSegments);
    float segmentedHeight = static_cast<float>(height) / static_cast<float>(heightSegments);

    for (auto iy = 0; iy <= heightSegments; iy++) {
        float y = iy * segmentedHeight - height / 2.0f;

        for (auto ix = 0; ix <= widthSegments; ix++, i++) {
            float x = ix * segmentedWidth - width / 2.0f;

            position[i * 3 + u] = x * uDirection;
            position[i * 3 + v] = y * vDirection;
            position[i * 3 + w] = depth / 2.0f;

            normal[i * 3 + u] = 0.0f;
            normal[i * 3 + v] = 0.0f;
            normal[i * 3 + w] = depth >= 0.0f ? 1.0f : -1.0f;

            uv[i * 2] = (float)ix / widthSegments;
            uv[i * 2 + 1] = 1.0f - (float)iy / heightSegments;

            if (iy == heightSegments || ix == widthSegments) continue;

            unsigned int a = io + ix + iy * (widthSegments + 1);
            unsigned int b = io + ix + (iy + 1) * (widthSegments + 1);
            unsigned int c = io + ix + (iy + 1) * (widthSegments + 1) + 1;
            unsigned int d = io + ix + iy * (widthSegments + 1) + 1;

            index[ii * 6] = a;
            index[ii * 6 + 1] = b;
            index[ii * 6 + 2] = d;
            index[ii * 6 + 3] = b;
            index[ii * 6 + 4] = c;
            index[ii * 6 + 5] = d;

            ii++;
        }
    }
}

}
