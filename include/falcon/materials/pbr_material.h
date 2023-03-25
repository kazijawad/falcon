#ifndef pbr_material_h
#define pbr_material_h

#include <falcon/core/material.h>
#include <falcon/falcon.h>

namespace falcon {

class PBRMaterial : public Material {
public:
    glm::vec4 baseColor;
    std::shared_ptr<ImageTexture> baseColorMap = nullptr;

    float metallic = 1.0;
    float roughness = 1.0;
    float ao = 1.0;

    PBRMaterial(glm::vec4 baseColor, float metallic, float roughness);
    PBRMaterial(std::shared_ptr<ImageTexture> baseColorMap, float metallic, float roughness);

    virtual void use(RenderState &state) override;
};

}

#endif
