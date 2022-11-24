#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <string>

#include <poly/loaders/gltf_loader.h>

namespace poly {

GLTFLoader::GLTFLoader() {}

void GLTFLoader::load(const std::string &filename) {
    std::string err;
    std::string warn;

    bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
    if (!warn.empty()) {
        std::printf("GLTF File Warning: %s\n", warn.c_str());
    }
    if (!err.empty()) {
        std::printf("GLTF File Error: %s\n", err.c_str());
        throw std::exception();
    }
    if (!ret) {
        std::printf("Failed to parse GLTF file\n");
        throw std::exception();
    }

    auto scene = model.scenes[model.defaultScene];
    for (auto i : scene.nodes) {
        auto node = model.nodes[i];
    }
}

}
