#ifndef gltf_loader_h
#define gltf_loader_h

#include <string>
#include <memory>

#include <tiny_gltf.h>

namespace poly {

class Transform;
class Geometry;

class GLTFLoader {
public:
    GLTFLoader();

    std::vector<std::shared_ptr<Transform>> load(const std::string &filename);
    std::shared_ptr<Transform> loadNode(int nodeIndex);
    std::vector<std::shared_ptr<Geometry>> loadMesh(int meshIndex);

private:
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
};

}

#endif
