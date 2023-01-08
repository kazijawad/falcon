#include <polyhedron/materials/shader_material.h>

namespace polyhedron {

ShaderMaterial::ShaderMaterial(
    const char* vertexPath,
    const char* fragmentPath,
    const char* geometryPath
) : Material(vertexPath, fragmentPath, geometryPath) {};

}
