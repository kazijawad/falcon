#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

#include <poly/loaders/gltf_loader.h>
#include <poly/core/mesh.h>
#include <poly/materials/normal_material.h>
#include <poly/materials/pbr_material.h>

namespace poly {

GLTFLoader::GLTFLoader() {}

std::vector<std::shared_ptr<Transform>> GLTFLoader::load(const std::string &filename) {
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

    std::vector<std::shared_ptr<Transform>> scenes(model.scenes.size());
    for (unsigned int i = 0; i < model.scenes.size(); i++) {
        auto scene = std::make_shared<Transform>();

        for (int nodeIndex : model.scenes[i].nodes) {
            auto transform = loadNode(nodeIndex);
            scene->add(transform);
        }

        scenes[i] = scene;
    }

    return scenes;
}

std::shared_ptr<Transform> GLTFLoader::loadNode(int nodeIndex) {
    auto node = model.nodes[nodeIndex];
    // TODO: Handle cameras and lights.

    auto transform = std::make_shared<Transform>();

    if (!node.matrix.empty()) {
        double* mat = &node.matrix[0];
        transform->localMatrix = glm::make_mat4(mat);
    }

    if (!node.rotation.empty()) {
        double* quat = &node.rotation[0];
        transform->rotation = glm::make_quat(quat);
    }

    if (node.mesh > -1) {
        auto meshes = loadMesh(node.mesh);
        for (auto mesh : meshes) {
            transform->add(mesh);
        }
    }

    if (!node.children.empty()) {
        for (auto childNodeIndex : node.children) {
            auto childTranform = loadNode(childNodeIndex);
            transform->add(childTranform);
        }
    }

    return transform;
}

std::vector<std::shared_ptr<Mesh>> GLTFLoader::loadMesh(int meshIndex) {
    auto mesh = model.meshes[meshIndex];
    std::vector<std::shared_ptr<Mesh>> meshes;

    for (auto primitive : mesh.primitives) {
        // TODO: Handle point and line rendering.
        if (primitive.mode && primitive.mode != 4) continue;

        // TODO: Handle material.
        auto geometry = loadGeometry(primitive);
        auto material = loadMaterial(primitive);

        meshes.push_back(std::make_shared<Mesh>(geometry, material));
    }

    return meshes;
}

std::shared_ptr<Geometry> GLTFLoader::loadGeometry(tinygltf::Primitive primitive) {
    std::vector<float> positions;
    std::vector<float> normals;
    std::vector<unsigned int> indices;

    if (primitive.attributes.count("POSITION") > 0) {
        auto accessorIndex = primitive.attributes.find("POSITION")->second;
        auto accessor = model.accessors[accessorIndex];

        if (accessor.type != TINYGLTF_TYPE_VEC3) {
            std::printf("Primitive position accessor is not of type VEC3: %d", accessorIndex);
        } else {
            auto bufferView = model.bufferViews[accessor.bufferView];
            auto buffer = model.buffers[bufferView.buffer];

            auto data = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
            for (size_t i = 0; i < accessor.count; i++) {
                positions.push_back(data[i * 3 + 0]);
                positions.push_back(data[i * 3 + 1]);
                positions.push_back(data[i * 3 + 2]);
            }
        }
    }

    if (primitive.attributes.count("NORMAL") > 0) {
        auto accessorIndex = primitive.attributes.find("NORMAL")->second;
        auto accessor = model.accessors[accessorIndex];

        if (accessor.type != TINYGLTF_TYPE_VEC3) {
            std::printf("Primitive normal accessor is not of type VEC3: %d", accessorIndex);
        } else {
            auto bufferView = model.bufferViews[accessor.bufferView];
            auto buffer = model.buffers[bufferView.buffer];

            auto data = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
            for (size_t i = 0; i < accessor.count; i++) {
                normals.push_back(data[i * 3 + 0]);
                normals.push_back(data[i * 3 + 1]);
                normals.push_back(data[i * 3 + 2]);
            }
        }
    }

    if (primitive.indices > -1) {
        auto accessorIndex = primitive.indices;
        auto accessor = model.accessors[accessorIndex];

        if (accessor.type != TINYGLTF_TYPE_SCALAR) {
            std::printf("Primitive index accessor is not of type SCALAR: %d", accessorIndex);
        } else {
            auto bufferView = model.bufferViews[accessor.bufferView];
            auto buffer = model.buffers[bufferView.buffer];

            switch (accessor.componentType) {
            case TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT: {
                auto data = reinterpret_cast<const uint32_t*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
                for (size_t i = 0; i < accessor.count; i++) {
                    indices.push_back(data[i]);
                }
                break;
            }
            case TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT: {
                auto data = reinterpret_cast<const uint16_t*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
                for (size_t i = 0; i < accessor.count; i++) {
                    indices.push_back(data[i]);
                }
                break;
            }
            case TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE: {
                auto data = reinterpret_cast<const uint8_t*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
                for (size_t i = 0; i < accessor.count; i++) {
                    indices.push_back(data[i]);
                }
                break;
            }
            }
        }
    }

    if (positions.size() != normals.size() && !normals.empty()) {
        std::printf("GLTF positions and normals are not equal: %zu, %zu", positions.size(), normals.size());
    }

    std::vector<Vertex> vertices;

    for (unsigned int i = 0; i < positions.size(); i += 3) {
        Vertex vertex;

        vertex.position = glm::vec3(positions[i], positions[i + 1], positions[i + 2]);

        if (i + 2 < normals.size()) {
            vertex.normal = glm::vec3(normals[i], normals[i + 1], normals[i + 2]);
        }

        vertices.push_back(vertex);
    }

    return std::make_shared<Geometry>(vertices, indices);
}

std::shared_ptr<Material> GLTFLoader::loadMaterial(tinygltf::Primitive primitive) {
    if (primitive.material > -1) {
        auto modelMaterial = model.materials[primitive.material];

        auto pbr = modelMaterial.pbrMetallicRoughness;
        auto baseColor = glm::vec4(
            pbr.baseColorFactor[0],
            pbr.baseColorFactor[1],
            pbr.baseColorFactor[2],
            pbr.baseColorFactor[3]
        );

        auto material = std::make_shared<PBRMaterial>(baseColor, pbr.metallicFactor, pbr.roughnessFactor);
        material->doubleSided = modelMaterial.doubleSided;

        return material;
    }

    return std::make_shared<NormalMaterial>();
}

}
