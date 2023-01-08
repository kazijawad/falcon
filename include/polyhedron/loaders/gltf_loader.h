#ifndef gltf_loader_h
#define gltf_loader_h

#include <string>
#include <memory>

#include <tiny_gltf.h>

namespace polyhedron {

class Transform;
class Mesh;
class Geometry;
class Material;

class GLTFLoader {
public:
    GLTFLoader();

    std::vector<std::shared_ptr<Transform>> load(const std::string &filename);
    std::shared_ptr<Transform> loadNode(int nodeIndex);
    std::vector<std::shared_ptr<Mesh>> loadMesh(int meshIndex);

    std::shared_ptr<Geometry> loadGeometry(tinygltf::Primitive primitive);
    std::shared_ptr<Material> loadMaterial(tinygltf::Primitive primitive);

private:
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
};

}

#endif
