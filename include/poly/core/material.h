#ifndef material_h
#define material_h

#include <poly/core/program.h>

namespace poly {

class Material {
public:
    Program program;

    bool isVisible = true;

    Material(Program program);
    Material(const char* vertexPath, const char* fragmentPath, const char* geometryPath = NULL);
};

}

#endif
