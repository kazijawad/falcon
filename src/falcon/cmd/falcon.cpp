#include <falcon/controls/orbit_controls.h>
#include <falcon/core/camera.h>
#include <falcon/core/renderer.h>
#include <falcon/lights/point_light.h>
#include <falcon/loaders/gltf_loader.h>
#include <falcon/falcon.h>
#include <falcon/utils/file_utils.h>

using namespace falcon;

int main() {
    try {
        Renderer renderer(1280, 720);
        renderer.setClearColor(0.1, 0.1, 0.1, 1.0);

        GLTFLoader loader;
        auto state = loader.load(FileUtils::getAssetPath("/assets/meshes/dragon/scene.gltf"));
        std::shared_ptr<Transform> scene = state.scenes[0];
        std::shared_ptr<Camera> camera = state.cameras[0];

        auto controls = OrbitControls(renderer.window, camera);

        scene->addChild(std::make_shared<PointLight>(glm::vec3(-2.0, 1.0, 0.0), glm::vec3(0.2, 0.2, 0.8)));
        scene->addChild(std::make_shared<PointLight>(glm::vec3(2.0, 1.0, 0.0), glm::vec3(1.0)));

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
