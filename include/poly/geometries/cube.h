#ifndef cube_h
#define cube_h

#include <poly/geometries/plane.h>

namespace poly {

class Cube : public Geometry {
public:
    Cube();
    Cube(int width, int height, int depth);
    Cube(
        int width,
        int height,
        int depth,
        unsigned int widthSegments,
        unsigned int heightSegments,
        unsigned int depthSegments
    );

    static std::tuple<std::vector<Vertex>, std::vector<unsigned int>> build(
        int width,
        int height,
        int depth,
        unsigned int widthSegments,
        unsigned int heightSegments,
        unsigned int depthSegments
    );
};

}

#endif
