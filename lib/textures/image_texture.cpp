#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include <polyhedron/textures/image_texture.h>

namespace polyhedron {

ImageTexture::ImageTexture(const std::string &path) {
    glGenTextures(1, &id);
    target = GL_TEXTURE_2D;

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &numComponents, 0);
    if (!data) {
        std::printf("Failed to read texture: %s\n", path.c_str());
    }

    if (numComponents == 3) {
        format = GL_RGB;
    } else if (numComponents == 4) {
        format = GL_RGBA;
    }

    glBindTexture(target, id);
    glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(target);

    if (format == GL_RGBA) {
        wrapS = GL_CLAMP_TO_EDGE;
        wrapT = GL_CLAMP_TO_EDGE;
    }
    glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
}

void ImageTexture::bind() {
    glBindTexture(target, id);
}

}
