#ifndef plane_h
#define plane_h

#include <falcon/core/geometry.h>

namespace falcon {

class Plane : public Geometry {
public:
    Plane(int width = 1, int height = 1, unsigned int widthSegments = 1, unsigned int heightSegments = 1);

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
