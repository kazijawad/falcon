#ifndef shader_material_h
#define shader_material_h

#include <polyhedron/core/material.h>

namespace polyhedron {

class ShaderMaterial : public Material {
public:
    ShaderMaterial(const char* vertexPath, const char* fragmentPath, const char* geometryPath = NULL);
};

}

#endif
