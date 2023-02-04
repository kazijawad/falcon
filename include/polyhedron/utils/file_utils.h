#ifndef file_utils_h
#define file_utils_h

#include <polyhedron/polyhedron.h>

namespace polyhedron {

class FileUtils {
public:
    static const std::string getExecutableDirectory();
    static const std::string getAssetPath(const std::string &relativePath);
};

}

#endif

