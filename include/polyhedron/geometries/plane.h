#ifndef plane_h
#define plane_h

#include <polyhedron/core/geometry.h>

namespace polyhedron {

class Plane : public Geometry {
public:
    Plane();
    Plane(int width, int height);
    Plane(int width, int height, unsigned int widthSegments, unsigned int heightSegments);

    static std::tuple<std::vector<Vertex>, std::vector<unsigned int>> build(
        int width,
        int height,
        unsigned int widthSegments,
        unsigned int heightSegments
    );

    static std::tuple<std::vector<Vertex>, std::vector<unsigned int>> build(
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
    );

    static void build(
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
    );
};

}

#endif
