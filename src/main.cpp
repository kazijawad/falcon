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

void loop(poly::Renderer &renderer);
void handleResize(GLFWwindow* window, int width, int height);

int main() {
    try {
        auto renderer = new poly::Renderer(1280, 720);
        renderer->clearColor = glm::vec4(0.1, 0.1, 0.1, 1.0);

        auto loader = new poly::GLTFLoader();
        auto scenes = loader->load("./assets/meshes/box/scene.gltf");

        auto scene = scenes[0];

        auto camera = std::make_shared<poly::Camera>(45.0, 1280.0 / 720.0, 0.1, 100.0);
        camera->position.z = 5.0;

        auto mesh = std::make_shared<poly::Mesh>(std::make_shared<poly::Cube>(), std::make_shared<poly::Program>(
            "./assets/shaders/normal/vertex.glsl",
            "./assets/shaders/normal/fragment.glsl"
        ));
        scene->add(mesh);

        renderer->scene = scene;
        renderer->camera = camera;

        renderer->run(loop);

        renderer->terminate();
        return 0;
    } catch (std::exception &e) {
        return -1;
    }
}

void loop(poly::Renderer &renderer) {
    renderer.render(renderer.scene, renderer.camera);
}
