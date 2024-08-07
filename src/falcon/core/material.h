#ifndef material_h
#define material_h

#include <falcon/falcon.h>

namespace falcon {

class Material {
public:
    bool depthTest = true;
    bool depthWrite = true;

    bool isTransparent = false;
    // TODO: Not handling this anywhere at the moment.
    bool isDoubleSided = false;

    Material(const std::string &vertexPath, const std::string &fragmentPath);

    virtual void use(RenderState &state);

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setFloat(const std::string &name, float value) const;
    void setFloatArray(const std::string &name, unsigned int index, float value) const;

    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;

    void setVec2Array(const std::string &name, unsigned int index, const glm::vec2 &value) const;
    void setVec2Array(const std::string &name, unsigned int index, float x, float y) const;

    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;

    void setVec3Array(const std::string &name, unsigned int index, const glm::vec3 &value) const;
    void setVec3Array(const std::string &name, unsigned int index, float x, float y, float z) const;

    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    void setVec4Array(const std::string &name, unsigned int index, const glm::vec4 &value) const;
    void setVec4Array(const std::string &name, unsigned int index, float x, float y, float z, float w) const;

    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

protected:
    unsigned int id;
};

}

#endif
