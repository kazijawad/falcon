#ifndef gltf_loader_h
#define gltf_loader_h

#include <string>

#include <tiny_gltf.h>

namespace poly {

class GLTFLoader {
public:
    GLTFLoader();

    void load(const std::string &filename);

private:
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
};

}

#endif
