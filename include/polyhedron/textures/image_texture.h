#ifndef image_texture_h
#define image_texture_h

#include <polyhedron/core/texture.h>

namespace polyhedron {

class ImageTexture : public Texture {
public:
    ImageTexture(const std::string &path);

    void bind() override;

private:
    int width = 0;
    int height = 0;
    int numComponents = 0;
};

}

#endif
