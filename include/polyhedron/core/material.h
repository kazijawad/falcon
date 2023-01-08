#ifndef material_h
#define material_h

#include <polyhedron/core/program.h>

namespace polyhedron {

class Material {
public:
    Program program;

    bool visible = true;
    bool doubleSided = false;

    Material(Program program);
    Material(const char* vertexPath, const char* fragmentPath, const char* geometryPath = NULL);

    virtual void use();
};

}

#endif
