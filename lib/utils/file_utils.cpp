#include <whereami.h>

#include <polyhedron/utils/file_utils.h>

namespace polyhedron {

const char* FileUtils::getExecutableDirectory() {
    auto dirnameLength = 0;

    auto length = wai_getExecutablePath(NULL, 0, &dirnameLength);
    if (length < 1) {
        std::printf("Failed to find executable path\n");
    }

    auto path = (char*)malloc(length + 1);
    if (!path) {
        std::printf("Failed to allocate memory for executable path\n");
    }

    wai_getExecutablePath(path, length, &dirnameLength);
    path[dirnameLength] = '\0';

    return path;
}

const char* FileUtils::getAssetPath(const char* relativePath) {
    auto execPath = getExecutableDirectory();

    auto assetPath = new char[strlen(execPath) + strlen(relativePath) + 1];
    strcpy(assetPath, execPath);
    strcat(assetPath, relativePath);

    return assetPath;
}

}
