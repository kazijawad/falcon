#include <iostream>
#include <memory>
#include <vector>
#include <exception>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <polyhedron/core/renderer.h>
#include <polyhedron/core/camera.h>
#include <polyhedron/core/transform.h>
#include <polyhedron/core/program.h>
#include <polyhedron/core/mesh.h>
#include <polyhedron/geometries/cube.h>
#include <polyhedron/loaders/gltf_loader.h>
#include <polyhedron/utils/file_utils.h>

using namespace polyhedron;

void loop(Renderer &renderer);

int main() {
    try {
        auto renderer = new Renderer(1280, 720);
        renderer->clearColor = glm::vec4(0.1, 0.1, 0.1, 1.0);

        auto camera = std::make_shared<Camera>(45.0, 1280.0 / 720.0, 0.1, 100.0);
        camera->position = glm::vec3(0.0, 3.0, 6.0);

        auto loader = new GLTFLoader();
        auto scenes = loader->load(FileUtils::getAssetPath("/assets/meshes/cornell_box/scene.gltf"));

        auto scene = scenes[0];

        renderer->scene = scene;
        renderer->camera = camera;

        renderer->run(loop);

        renderer->terminate();
        return 0;
    } catch (std::exception &e) {
        return -1;
    }
}

void loop(Renderer &renderer) {
    renderer.render();
}
