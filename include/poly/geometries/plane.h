#ifndef plane_h
#define plane_h

#include <poly/core/geometry.h>

namespace poly {

class Plane : public Geometry {
public:
    Plane();
    Plane(unsigned int width, unsigned int height);
    Plane(unsigned int width, unsigned int height, unsigned int widthSegments, unsigned int heightSegments);

    static std::tuple<std::vector<Vertex>, std::vector<unsigned int>> build(
        unsigned int width,
        unsigned int height,
        unsigned int widthSegments,
        unsigned int heightSegments
    );

    static std::tuple<std::vector<Vertex>, std::vector<unsigned int>> build(
        unsigned int width,
        unsigned int height,
        unsigned int depth,
        unsigned int widthSegments,
        unsigned int heightSegments,
        float uDirection,
        float vDirection,
        unsigned int i,
        unsigned int ii
    );
};

}

#endif
