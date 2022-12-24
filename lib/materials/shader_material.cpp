#include <poly/materials/shader_material.h>

namespace poly {

ShaderMaterial::ShaderMaterial(
    const char* vertexPath,
    const char* fragmentPath,
    const char* geometryPath
) : Material(vertexPath, fragmentPath, geometryPath) {};

}
