#include <iostream>
#include <memory>
#include <vector>
#include <exception>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <poly/core/renderer.h>
#include <poly/core/camera.h>
#include <poly/core/transform.h>
#include <poly/core/program.h>
#include <poly/core/mesh.h>
#include <poly/geometries/cube.h>
#include <poly/loaders/gltf_loader.h>

using namespace poly;

void loop(Renderer &renderer);

int main() {
    try {
        auto renderer = new Renderer(1280, 720);
        renderer->clearColor = glm::vec4(0.1, 0.1, 0.1, 1.0);

        auto camera = std::make_shared<Camera>(45.0, 1280.0 / 720.0, 0.1, 100.0);
        camera->position = glm::vec3(0.0, 3.0, 6.0);

        auto loader = new GLTFLoader();
        auto scenes = loader->load("./assets/meshes/box/scene.gltf");

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
