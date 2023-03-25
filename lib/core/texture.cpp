#include <falcon/core/texture.h>

namespace falcon {

Texture::Texture() {}

GLenum Texture::getFormat() {
    return format;
}

GLenum Texture::getWrapS() {
    return wrapS;
}

void Texture::setWrapS(GLenum v) {
    if (v == wrapS) return;
    bind();
    glTexParameteri(target, GL_TEXTURE_WRAP_S, v);
    wrapS = v;
}

GLenum Texture::getWrapT() {
    return wrapT;
}

void Texture::setWrapT(GLenum v) {
    if (v == wrapT) return;
    bind();
    glTexParameteri(target, GL_TEXTURE_WRAP_T, v);
    wrapT = v;
}

GLenum Texture::getMinFilter() {
    return minFilter;
}

void Texture::setMinFilter(GLenum v) {
    if (v == minFilter) return;
    bind();
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, v);
    minFilter = v;
}

GLenum Texture::getMagFilter() {
    return magFilter;
}

void Texture::setMagFilter(GLenum v) {
    if (v == magFilter) return;
    bind();
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, v);
    magFilter = v;
}

}
