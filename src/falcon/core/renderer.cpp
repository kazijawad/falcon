#include <falcon/core/camera.h>
#include <falcon/core/material.h>
#include <falcon/core/mesh.h>
#include <falcon/core/renderer.h>
#include <falcon/lights/point_light.h>

namespace falcon {

Renderer::Renderer(unsigned int width, unsigned int height) : width(width), height(height) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* newWindow = glfwCreateWindow(width, height, "falcon", NULL, NULL);
    if (newWindow == NULL) {
        std::printf("Failed to create GLFW window\n");
        glfwTerminate();
        throw std::exception();
    }

    window = newWindow;
    glfwMakeContextCurrent(window);

    if (gladLoadGL(glfwGetProcAddress) == 0) {
        std::printf("Failed to initialize OpenGL Context\n");
        throw std::exception();
    }

    // Enable GL capabilities.
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    std::printf("Vender: %s\n", glGetString(GL_VENDOR));
    std::printf("Renderer: %s\n", glGetString(GL_RENDERER));
    std::printf("Version: %s\n", glGetString(GL_VERSION));
}

Renderer::~Renderer() {
    terminate();
}

unsigned int Renderer::getWidth() {
    return width;
}

unsigned int Renderer::getHeight() {
    return height;
}

float Renderer::getAspectRatio() {
    return static_cast<float>(width) / static_cast<float>(height);
}

void Renderer::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Renderer::setDepthTest(bool v) {
    if (v == state.depthTest) return;
    if (v) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
    state.depthTest = v;
}

void Renderer::setDepthMask(bool v) {
    if (v == state.depthMask) return;
    if (v) {
        glDepthMask(GL_TRUE);
    } else {
        glDepthMask(GL_FALSE);
    }
    state.depthMask = v;
}

void Renderer::setBlendFunc(int src, int dst) {
    if (src == state.srcBlendFactor && dst == state.dstBlendFactor) return;
    glBlendFunc(src, dst);
    state.srcBlendFactor = src;
    state.dstBlendFactor = dst;
}

void Renderer::clearColor() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::clearDepth() {
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::clearStencil() {
    glClear(GL_STENCIL_BUFFER_BIT);
}

void Renderer::clear(bool color, bool depth, bool stencil) {
    glClear(GL_COLOR_BUFFER_BIT | (depth ? GL_DEPTH_BUFFER_BIT : 0) | (stencil ? GL_STENCIL_BUFFER_BIT : 0));
}

void Renderer::run(std::function<void()> fn) {
    while (!glfwWindowShouldClose(window)) {
        fn();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Renderer::render(std::shared_ptr<Transform> scene, std::shared_ptr<Camera> camera) {
    // TODO: Move outside of render loop.
    if (handleResize()) {
        // TODO: Need to improve, assumes the same camera
        // used between renders.
        camera->handleResize(width, height);
    }

    scene->updateWorld();
    camera->updateWorld();

    updateRenderState(scene, camera);

    for (std::shared_ptr<Mesh> mesh : state.meshes) {
        setDepthTest(mesh->material->depthTest);
        setDepthMask(mesh->material->depthWrite);

        if (mesh->material->isTransparent) {
            setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        mesh->draw(state);
    }
}

void Renderer::terminate() {
    glfwTerminate();
}

bool Renderer::handleResize() {
    int newWidth, newHeight;
    glfwGetFramebufferSize(window, &newWidth, &newHeight);

    if (newWidth != width || newHeight != height) {
        glViewport(0, 0, newWidth, newHeight);

        width = newWidth;
        height = newHeight;

        return true;
    }

    return false;
}

void Renderer::updateRenderState(std::shared_ptr<Transform> scene, std::shared_ptr<Camera> camera) {
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Mesh>> transparent;

    std::vector<std::shared_ptr<Light>> lights;

    scene->traverse([&](std::shared_ptr<Transform> transform) mutable {
        if (transform->isVisible) {
            if (std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(transform)) {
                // TODO: Test for frustum culling?
                if (mesh->material->isTransparent) {
                    transparent.push_back(mesh);
                } else {
                    meshes.push_back(mesh);
                }
            }

            if (std::shared_ptr<PointLight> light = std::dynamic_pointer_cast<PointLight>(transform)) {
                lights.push_back(light);
            }

            return false;
        }
        return true;
    });

    // Sort transparent meshes by depth relative to camera.
    auto cameraPosition = camera->getTranslation();
    std::sort(
        transparent.begin(),
        transparent.end(),
        [&cameraPosition](std::shared_ptr<Mesh> a, std::shared_ptr<Mesh> b) {
            auto aDist = glm::length(cameraPosition - a->getTranslation());
            auto bDist = glm::length(cameraPosition - b->getTranslation());
            return aDist < bDist;
        }
    );
    meshes.insert(meshes.end(), transparent.begin(), transparent.end());

    state.camera = camera;
    state.meshes = meshes;
    state.lights = lights;
}

}
