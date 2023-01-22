#include <polyhedron/core/camera.h>
#include <polyhedron/core/mesh.h>
#include <polyhedron/core/renderer.h>

namespace polyhedron {

Renderer::Renderer(unsigned int width, unsigned int height) {
    state.width = width;
    state.height = height;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* newWindow = glfwCreateWindow(state.width, state.height, "Polyhedron", NULL, NULL);
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

    // Enable MSAA
    glEnable(GL_MULTISAMPLE);

    std::printf("Vender: %s\n", glGetString(GL_VENDOR));
    std::printf("Renderer: %s\n", glGetString(GL_RENDERER));
    std::printf("Version: %s\n", glGetString(GL_VERSION));
}

Renderer::~Renderer() { terminate(); }

unsigned int Renderer::width() { return state.width; }

unsigned int Renderer::height() { return state.height; }

float Renderer::aspectRatio() { return (float)state.width / (float)state.height; }

void Renderer::setClearColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }

void Renderer::clearColor() { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::clearDepth() { glClear(GL_DEPTH_BUFFER_BIT); }

void Renderer::clearStencil() { glClear(GL_STENCIL_BUFFER_BIT); }

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
    if (handleResize()) {
        // TODO: Need to improve, assumes the same camera
        // used between renders.
        camera->handleResize(state.width, state.height);
    }

    scene->updateWorldMatrix();
    camera->updateWorldMatrix();

    auto meshes = getRenderList(scene, camera);
    for (std::shared_ptr<Mesh> mesh : meshes) {
        mesh->draw(camera);
    }
}

void Renderer::terminate() { glfwTerminate(); }

bool Renderer::handleResize() {
    int newWidth, newHeight;
    glfwGetFramebufferSize(window, &newWidth, &newHeight);

    if (newWidth != state.width || newHeight != state.height) {
        glViewport(0, 0, newWidth, newHeight);

        state.width = newWidth;
        state.height = newHeight;

        return true;
    }

    return false;
}

std::vector<std::shared_ptr<Mesh>>
Renderer::getRenderList(std::shared_ptr<Transform> scene, std::shared_ptr<Camera> camera) {
    std::vector<std::shared_ptr<Mesh>> meshes;

    scene->traverse([&meshes](std::shared_ptr<Transform> transform) mutable {
        if (transform->isVisible) {
            if (std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(transform)) {
                // TODO: Test for frustum culling?
                meshes.push_back(mesh);
            }
            return false;
        }
        return true;
    });

    // TODO: Add sorting.

    return meshes;
}

}
