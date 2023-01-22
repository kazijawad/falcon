#ifndef file_utils_h
#define file_utils_h

#include <polyhedron/polyhedron.h>

namespace polyhedron {

class FileUtils {
public:
    static const char* getExecutableDirectory();
    static const char* getAssetPath(const char* relativePath);
};

}

#endif

