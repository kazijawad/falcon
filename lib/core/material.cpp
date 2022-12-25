#include <poly/core/material.h>

namespace poly {

Material::Material(Program program): program(program) {}

Material::Material(
    const char* vertexPath,
    const char* fragmentPath,
    const char* geometryPath
) : program(vertexPath, fragmentPath, geometryPath) {};

void Material::use() {
    program.use();
}

}
