#ifndef texture_h
#define texture_h

#include <falcon/falcon.h>

namespace falcon {

class Texture {
public:
    Texture() {};
    virtual ~Texture() = default;

    GLenum getFormat() const;

    GLenum getWrapS() const;
    void setWrapS(GLenum v);

    GLenum getWrapT() const;
    void setWrapT(GLenum v);

    GLenum getMinFilter() const;
    void setMinFilter(GLenum v);

    GLenum getMagFilter() const;
    void setMagFilter(GLenum v);

    virtual void bind() = 0;

protected:
    unsigned int id = 0;
    GLenum target = GL_TEXTURE_2D;

    GLenum format = GL_RED;
    GLenum wrapS = GL_REPEAT;
    GLenum wrapT = GL_REPEAT;

    GLenum minFilter = GL_LINEAR_MIPMAP_LINEAR;
    GLenum magFilter = GL_LINEAR;
};

}

#endif
