#include <falcon/core/texture.h>

namespace falcon {

GLenum Texture::getFormat() const {
    return format;
}

GLenum Texture::getWrapS() const {
    return wrapS;
}

void Texture::setWrapS(GLenum v) {
    if (v == wrapS) return;
    bind();
    glTexParameteri(target, GL_TEXTURE_WRAP_S, v);
    wrapS = v;
}

GLenum Texture::getWrapT() const {
    return wrapT;
}

void Texture::setWrapT(GLenum v) {
    if (v == wrapT) return;
    bind();
    glTexParameteri(target, GL_TEXTURE_WRAP_T, v);
    wrapT = v;
}

GLenum Texture::getMinFilter() const {
    return minFilter;
}

void Texture::setMinFilter(GLenum v) {
    if (v == minFilter) return;
    bind();
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, v);
    minFilter = v;
}

GLenum Texture::getMagFilter() const {
    return magFilter;
}

void Texture::setMagFilter(GLenum v) {
    if (v == magFilter) return;
    bind();
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, v);
    magFilter = v;
}

}
