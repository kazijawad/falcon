#include <iostream>
#include <memory>
#include <vector>
#include <exception>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <polyhedron/core/renderer.h>
#include <polyhedron/core/camera.h>
#include <polyhedron/loaders/gltf_loader.h>
#include <polyhedron/utils/file_utils.h>

using namespace polyhedron;

int main() {
    try {
        Renderer renderer(1280, 720);
        renderer.setClearColor(0.1, 0.1, 0.1, 1.0);

        auto camera = std::make_shared<Camera>(45.0, 1280.0 / 720.0, 0.1, 100.0);
        camera->applyTranslation(0.0, 3.0, 6.0);

        GLTFLoader loader;
        std::shared_ptr<Transform> scene = loader.load(
            FileUtils::getAssetPath("/assets/meshes/cornell_box/scene.gltf")
        )[0];

        renderer.run([renderer, scene, camera]() mutable {
            renderer.clear();
            renderer.render(scene, camera);
        });

        return 0;
    } catch (std::exception &e) {
        return -1;
    }
}
