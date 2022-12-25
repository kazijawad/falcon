#ifndef material_h
#define material_h

#include <poly/core/program.h>

namespace poly {

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
