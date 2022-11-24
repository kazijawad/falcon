#include <iostream>
#include <memory>
#include <exception>

#include <glad/gl.h>

#include <poly/core/renderer.h>
#include <poly/core/mesh.h>

namespace poly {

Renderer::Renderer(unsigned int width, unsigned int height) : Renderer(width, height, true) {}

Renderer::Renderer(unsigned int width, unsigned int height, bool isDebug) : width(width), height(height), isDebug(isDebug) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* newWindow = glfwCreateWindow(width, height, "Poly", NULL, NULL);
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

    if (isDebug) {
        std::printf("Vender: %s\n", glGetString(GL_VENDOR));
        std::printf("Renderer: %s\n", glGetString(GL_RENDERER));
        std::printf("Version: %s\n", glGetString(GL_VERSION));
    }

    glEnable(GL_DEPTH_TEST);
}

void Renderer::setClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
}

void Renderer::run(void (*f)(Renderer &renderer)) {
    while (!glfwWindowShouldClose(window)) {
        elapsedTime = (float) glfwGetTime();

        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        (*f)(*this);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Renderer::render(std::shared_ptr<Transform> scene, std::shared_ptr<Camera> camera) {
    camera->updateWorldMatrix();
    for (auto child : scene->children) {
        child->draw(camera);
    }
}

void Renderer::terminate() {
    glfwTerminate();
}

}
