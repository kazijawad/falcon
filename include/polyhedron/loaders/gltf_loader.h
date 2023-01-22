#ifndef gltf_loader_h
#define gltf_loader_h

#include <tiny_gltf.h>

#include <polyhedron/polyhedron.h>

namespace polyhedron {

struct GLTFState {
    std::vector<std::shared_ptr<Camera>> cameras;
    std::vector<std::shared_ptr<Transform>> scenes;
};

class GLTFLoader {
public:
    GLTFLoader();

    GLTFState load(const std::string &filename);
    std::shared_ptr<Transform> loadNode(GLTFState &state, int nodeIndex);
    std::vector<std::shared_ptr<Mesh>> loadMesh(int meshIndex);

    std::shared_ptr<Geometry> loadGeometry(tinygltf::Primitive primitive);
    std::shared_ptr<Material> loadMaterial(tinygltf::Primitive primitive);

private:
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
};

}

#endif
