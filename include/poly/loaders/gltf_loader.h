#ifndef gltf_loader_h
#define gltf_loader_h

#include <string>

#include <tiny_gltf.h>

namespace poly {

class Transform;
class Mesh;

class GLTFLoader {
public:
    GLTFLoader();

    std::vector<std::shared_ptr<Transform>> load(const std::string &filename);
    std::shared_ptr<Transform> loadNode(int nodeIndex);
    std::vector<std::shared_ptr<Mesh>> loadMesh(int meshIndex);

private:
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
};

}

#endif
