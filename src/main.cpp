#include <iostream>
#include <memory>
#include <vector>
#include <exception>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <polyhedron/core/renderer.h>
#include <polyhedron/cameras/perspective_camera.h>
#include <polyhedron/loaders/gltf_loader.h>
#include <polyhedron/utils/file_utils.h>

using namespace polyhedron;

int main() {
    try {
        Renderer renderer(1280, 720);
        renderer.setClearColor(0.1, 0.1, 0.1, 1.0);

        GLTFLoader loader;
        auto state = loader.load(FileUtils::getAssetPath("/assets/meshes/cornell_box/scene.gltf"));
        std::shared_ptr<Transform> scene = state.scenes[0];
        std::shared_ptr<Camera> camera = state.cameras[0];

        renderer.run([renderer, scene, camera]() mutable {
            renderer.clear();
            renderer.render(scene, camera);
        });

        return 0;
    } catch (std::exception &e) {
        return -1;
    }
}
