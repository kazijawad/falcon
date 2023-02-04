#include <whereami.h>

#include <polyhedron/utils/file_utils.h>

namespace polyhedron {

const std::string FileUtils::getExecutableDirectory() {
    int dirnameLength = 0;
    int length = wai_getExecutablePath(nullptr, 0, &dirnameLength);
    if (length < 1) {
        std::printf("Failed to find executable path\n");
    }

    char* path = new char[length + 1];
    wai_getExecutablePath(path, length, &dirnameLength);
    path[dirnameLength] = '\0';

    std::string executablePath(path);
    delete[] path;

    return executablePath;
}

const std::string FileUtils::getAssetPath(const std::string &relativePath) {
    return getExecutableDirectory() + relativePath;
}

}
