#ifndef cube_h
#define cube_h

#include <polyhedron/geometries/plane.h>

namespace polyhedron {

class Cube : public Geometry {
public:
    Cube(
        int width = 1,
        int height = 1,
        int depth = 1,
        unsigned int widthSegments = 1,
        unsigned int heightSegments = 1,
        unsigned int depthSegments = 1
    );
};

}

#endif
