#ifndef file_utils_h
#define file_utils_h

#include <string>

namespace poly {

class FileUtils {
public:
    static const char* getExecutableDirectory();
    static const char* getAssetPath(const char* relativePath);
};

}

#endif

