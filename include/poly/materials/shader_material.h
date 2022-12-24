#ifndef shader_material_h
#define shader_material_h

#include <poly/core/material.h>

namespace poly {

class ShaderMaterial : public Material {
public:
    ShaderMaterial(const char* vertexPath, const char* fragmentPath, const char* geometryPath = NULL);
};

}

#endif
