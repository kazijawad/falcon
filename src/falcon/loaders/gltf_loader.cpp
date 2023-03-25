#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <falcon/cameras/orthographic_camera.h>
#include <falcon/cameras/perspective_camera.h>
#include <falcon/core/geometry.h>
#include <falcon/core/mesh.h>
#include <falcon/loaders/gltf_loader.h>
#include <falcon/materials/normal_material.h>
#include <falcon/materials/pbr_material.h>
#include <falcon/textures/image_texture.h>
#include <falcon/utils/file_utils.h>

namespace falcon {

GLTFLoader::GLTFLoader() {}

GLTFState GLTFLoader::load(const std::string &filename) {
    path = filename;

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

    GLTFState state;
    state.cameras = std::vector<std::shared_ptr<Camera>>();
    state.scenes = std::vector<std::shared_ptr<Transform>>();

    state.cameras.reserve(model.cameras.size());
    state.scenes.reserve(model.scenes.size());

    for (tinygltf::Camera camera : model.cameras) {
        if (camera.type == "perspective") {
            state.cameras.push_back(std::make_shared<PerspectiveCamera>(
                glm::degrees(camera.perspective.yfov),
                camera.perspective.aspectRatio,
                camera.perspective.znear,
                camera.perspective.zfar
            ));
        } else if (camera.type == "orthographic") {
            state.cameras.push_back(std::make_shared<OrthographicCamera>(
                -camera.orthographic.xmag,
                camera.orthographic.xmag,
                -camera.orthographic.ymag,
                camera.orthographic.ymag,
                camera.orthographic.znear,
                camera.orthographic.zfar
            ));
        }
    }

    for (tinygltf::Scene glTFScene : model.scenes) {
        auto scene = std::make_shared<Transform>();

        for (int nodeIndex : glTFScene.nodes) {
            auto transform = loadNode(state, nodeIndex);
            scene->addChild(transform);
        }

        state.scenes.push_back(scene);
    }

    // Create a default camera if no cameras are set.
    if (state.cameras.empty()) {
        std::shared_ptr<Transform> scene = state.scenes[0];

        auto camera = std::make_shared<PerspectiveCamera>(45.0, 16.0 / 9.0, 0.1, 100.0);
        camera->setTranslation(-5.0, 0.0, 0.0);
        camera->lookAt(scene->getTranslation());

        state.cameras.push_back(camera);
    }

    return state;
}

std::shared_ptr<Transform> GLTFLoader::loadNode(GLTFState &state, int nodeIndex) {
    tinygltf::Node node = model.nodes[nodeIndex];
    // TODO: Handle lights.

    std::shared_ptr<Transform> transform;
    if (node.camera > -1) {
        transform = state.cameras[node.camera];
    } else {
        transform = std::make_shared<Transform>();
    }

    if (!node.translation.empty()) {
        double* translation = &node.translation[0];
        transform->setTranslation(translation[0], translation[1], translation[2]);
    }

    if (!node.scale.empty()) {
        double* scale = &node.scale[0];
        transform->setScale(scale[0], scale[1], scale[2]);
    }

    if (!node.rotation.empty()) {
        double* quat = &node.rotation[0];
        transform->setRotation(quat[3], glm::vec3(quat[0], quat[1], quat[2]));
    }

    if (!node.matrix.empty()) {
        double* mat = &node.matrix[0];
        transform->setLocal(glm::make_mat4(mat));
    } else if (node.camera > -1) {
        // The view direction is along the negative z-axis
        // if no transformation is defined.
        if (std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(transform)) {
            auto translation = camera->getTranslation();
            camera->lookAt(glm::vec3(translation.x, translation.y, -translation.z));
        }
    }

    if (node.mesh > -1) {
        auto meshes = loadMesh(node.mesh);
        for (std::shared_ptr<Mesh> mesh : meshes) {
            transform->addChild(mesh);
        }
    }

    if (!node.children.empty()) {
        for (auto childNodeIndex : node.children) {
            auto childTranform = loadNode(state, childNodeIndex);
            transform->addChild(childTranform);
        }
    }

    return transform;
}

std::vector<std::shared_ptr<Mesh>> GLTFLoader::loadMesh(int meshIndex) {
    tinygltf::Mesh mesh = model.meshes[meshIndex];

    std::vector<std::shared_ptr<Mesh>> meshes;
    meshes.reserve(mesh.primitives.size());

    for (tinygltf::Primitive primitive : mesh.primitives) {
        // TODO: Handle point and line rendering.
        if (primitive.mode && primitive.mode != 4) continue;

        auto geometry = loadGeometry(primitive);
        auto material = loadMaterial(primitive);

        meshes.push_back(std::make_shared<Mesh>(geometry, material));
    }

    return meshes;
}

std::shared_ptr<Geometry> GLTFLoader::loadGeometry(tinygltf::Primitive primitive) {
    std::vector<float> positions;
    std::vector<float> normals;
    std::vector<float> uvs;
    std::vector<unsigned int> indices;

    if (primitive.attributes.count("POSITION") > 0) {
        auto accessorIndex = primitive.attributes.find("POSITION")->second;
        tinygltf::Accessor accessor = model.accessors[accessorIndex];

        if (accessor.type != TINYGLTF_TYPE_VEC3) {
            std::printf("Primitive position accessor is not of type VEC3: %d", accessorIndex);
        } else {
            tinygltf::BufferView bufferView = model.bufferViews[accessor.bufferView];
            tinygltf::Buffer buffer = model.buffers[bufferView.buffer];

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
        tinygltf::Accessor accessor = model.accessors[accessorIndex];

        if (accessor.type != TINYGLTF_TYPE_VEC3) {
            std::printf("Primitive normal accessor is not of type VEC3: %d", accessorIndex);
        } else {
            tinygltf::BufferView bufferView = model.bufferViews[accessor.bufferView];
            tinygltf::Buffer buffer = model.buffers[bufferView.buffer];

            auto data = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
            for (size_t i = 0; i < accessor.count; i++) {
                normals.push_back(data[i * 3 + 0]);
                normals.push_back(data[i * 3 + 1]);
                normals.push_back(data[i * 3 + 2]);
            }
        }
    }

    if (primitive.attributes.count("TEXCOORD_0") > 0) {
        auto accessorIndex = primitive.attributes.find("TEXCOORD_0")->second;
        tinygltf::Accessor accessor = model.accessors[accessorIndex];

        if (accessor.type != TINYGLTF_TYPE_VEC2) {
            std::printf("Primitive uv accessor is not of type VEC2: %d", accessorIndex);
        } else {
            tinygltf::BufferView bufferView = model.bufferViews[accessor.bufferView];
            tinygltf::Buffer buffer = model.buffers[bufferView.buffer];

            auto data = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
            for (size_t i = 0; i < accessor.count; i++) {
                uvs.push_back(data[i * 2 + 0]);
                uvs.push_back(data[i * 2 + 1]);
            }
        }
    }

    if (primitive.indices > -1) {
        auto accessorIndex = primitive.indices;
        tinygltf::Accessor accessor = model.accessors[accessorIndex];

        if (accessor.type != TINYGLTF_TYPE_SCALAR) {
            std::printf("Primitive index accessor is not of type SCALAR: %d", accessorIndex);
        } else {
            tinygltf::BufferView bufferView = model.bufferViews[accessor.bufferView];
            tinygltf::Buffer buffer = model.buffers[bufferView.buffer];

            switch (accessor.componentType) {
            case TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT: {
                auto data =
                    reinterpret_cast<const uint32_t*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
                for (size_t i = 0; i < accessor.count; i++) {
                    indices.push_back(data[i]);
                }
                break;
            }
            case TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT: {
                auto data =
                    reinterpret_cast<const uint16_t*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);
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

    unsigned int vertexCount = positions.size() / 3;
    vertices.reserve(vertexCount);
    for (auto i = 0; i < vertexCount; ++i) {
        Vertex vertex = {
            glm::vec3(positions[i * 3], positions[i * 3 + 1], positions[i * 3 + 2]),
            glm::vec3(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]),
            glm::vec2(uvs[i * 2], uvs[i * 2 + 1])
        };
        vertices.push_back(vertex);
    }

    return std::make_shared<Geometry>(vertices, indices);
}

std::shared_ptr<Material> GLTFLoader::loadMaterial(tinygltf::Primitive primitive) {
    if (primitive.material > -1) {
        tinygltf::Material modelMaterial = model.materials[primitive.material];
        std::shared_ptr<PBRMaterial> material;

        tinygltf::PbrMetallicRoughness pbr = modelMaterial.pbrMetallicRoughness;
        if (pbr.baseColorTexture.index > -1) {
            tinygltf::Texture texture = model.textures[pbr.baseColorTexture.index];

            tinygltf::Image image = model.images[texture.source];
            tinygltf::Sampler sampler = model.samplers[texture.sampler];

            auto imageTexture = std::make_shared<ImageTexture>(FileUtils::getDirectory(path) + "\\" + image.uri);

            if (sampler.minFilter > -1) {
                if (sampler.minFilter == TINYGLTF_TEXTURE_FILTER_NEAREST) {
                    imageTexture->setMinFilter(GL_NEAREST);
                } else if (sampler.minFilter == TINYGLTF_TEXTURE_FILTER_LINEAR) {
                    imageTexture->setMinFilter(GL_LINEAR);
                } else if (sampler.minFilter == TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST) {
                    imageTexture->setMinFilter(GL_NEAREST_MIPMAP_NEAREST);
                } else if (sampler.minFilter == TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST) {
                    imageTexture->setMinFilter(GL_LINEAR_MIPMAP_NEAREST);
                } else if (sampler.minFilter == TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR) {
                    imageTexture->setMinFilter(GL_NEAREST_MIPMAP_LINEAR);
                } else if (sampler.minFilter == TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR) {
                    imageTexture->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
                }
            }

            if (sampler.magFilter > -1) {
                if (sampler.magFilter == TINYGLTF_TEXTURE_FILTER_NEAREST) {
                    imageTexture->setMagFilter(GL_NEAREST);
                } else if (sampler.magFilter == TINYGLTF_TEXTURE_FILTER_LINEAR) {
                    imageTexture->setMagFilter(GL_LINEAR);
                }
            }

            if (sampler.wrapS == TINYGLTF_TEXTURE_WRAP_REPEAT) {
                imageTexture->setWrapS(GL_REPEAT);
            } else if (sampler.wrapS == TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE) {
                imageTexture->setWrapS(GL_CLAMP_TO_EDGE);
            } else if (sampler.wrapS == TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT) {
                imageTexture->setWrapS(GL_MIRRORED_REPEAT);
            }

            if (sampler.wrapT == TINYGLTF_TEXTURE_WRAP_REPEAT) {
                imageTexture->setWrapT(GL_REPEAT);
            } else if (sampler.wrapT == TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE) {
                imageTexture->setWrapT(GL_CLAMP_TO_EDGE);
            } else if (sampler.wrapT == TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT) {
                imageTexture->setWrapT(GL_MIRRORED_REPEAT);
            }

            material = std::make_shared<PBRMaterial>(imageTexture, pbr.metallicFactor, pbr.roughnessFactor);
        } else {
            glm::vec4 baseColor(
                pbr.baseColorFactor[0], pbr.baseColorFactor[1], pbr.baseColorFactor[2], pbr.baseColorFactor[3]
            );
            material = std::make_shared<PBRMaterial>(baseColor, pbr.metallicFactor, pbr.roughnessFactor);
        }

        material->isDoubleSided = modelMaterial.doubleSided;
        if (modelMaterial.alphaMode == "BLEND") {
            material->isTransparent = true;
        } else if (modelMaterial.alphaMode == "MASK" && (modelMaterial.alphaCutoff > material->baseColor.a || modelMaterial.alphaCutoff > 1.0)) {
            material->isTransparent = true;
        }

        return material;
    }

    return std::make_shared<NormalMaterial>();
}

}
