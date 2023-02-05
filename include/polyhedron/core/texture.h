#ifndef texture_h
#define texture_h

#include <polyhedron/polyhedron.h>

namespace polyhedron {

class Texture {
public:
    Texture();
    virtual ~Texture() = default;

    GLenum getFormat();

    GLenum getWrapS();
    void setWrapS(GLenum v);

    GLenum getWrapT();
    void setWrapT(GLenum v);

    GLenum getMinFilter();
    void setMinFilter(GLenum v);

    GLenum getMagFilter();
    void setMagFilter(GLenum v);

    virtual void bind() = 0;

protected:
    unsigned int id;
    GLenum target;

    GLenum format = GL_RED;
    GLenum wrapS = GL_REPEAT;
    GLenum wrapT = GL_REPEAT;

    GLenum minFilter = GL_LINEAR_MIPMAP_LINEAR;
    GLenum magFilter = GL_LINEAR;
};

}

#endif
