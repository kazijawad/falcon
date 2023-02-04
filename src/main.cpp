#include <polyhedron/controls/orbit_controls.h>
#include <polyhedron/core/camera.h>
#include <polyhedron/core/renderer.h>
#include <polyhedron/loaders/gltf_loader.h>
#include <polyhedron/polyhedron.h>
#include <polyhedron/utils/file_utils.h>

using namespace polyhedron;

int main() {
    try {
        Renderer renderer(1280, 720);
        renderer.setClearColor(0.1, 0.1, 0.1, 1.0);

        GLTFLoader loader;
        auto state = loader.load(FileUtils::getAssetPath("/assets/meshes/dragon/scene.gltf"));
        std::shared_ptr<Transform> scene = state.scenes[0];
        std::shared_ptr<Camera> camera = state.cameras[0];

        auto controls = OrbitControls(renderer.window, camera);

        renderer.run([&]() mutable {
            controls.update();

            renderer.clear();
            renderer.render(scene, camera);
        });

        return 0;
    } catch (std::exception &e) {
        return -1;
    }
}
