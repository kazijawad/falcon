#include <iostream>
#include <memory>
#include <exception>

#include <glad/gl.h>

#include <polyhedron/core/renderer.h>
#include <polyhedron/core/mesh.h>

namespace polyhedron {

Renderer::Renderer(unsigned int width, unsigned int height) : Renderer(width, height, true) {}

Renderer::Renderer(unsigned int width, unsigned int height, bool isDebug) : width(width), height(height), isDebug(isDebug) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

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

    // Enable MSAA
    glEnable(GL_MULTISAMPLE);

    if (isDebug) {
        std::printf("Vender: %s\n", glGetString(GL_VENDOR));
        std::printf("Renderer: %s\n", glGetString(GL_RENDERER));
        std::printf("Version: %s\n", glGetString(GL_VERSION));
    }
}

void Renderer::run(void (*f)(Renderer &renderer)) {
    while (!glfwWindowShouldClose(window)) {
        elapsedTime = (float) glfwGetTime();
        resize();

        if (depthTest) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }

        if (stencilTest) {
            glEnable(GL_STENCIL_TEST);
        } else {
            glDisable(GL_STENCIL_TEST);
        }

        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        if (autoClear) {
            glClear(GL_COLOR_BUFFER_BIT | (depthTest ? GL_DEPTH_BUFFER_BIT : 0) | (stencilTest ? GL_STENCIL_BUFFER_BIT : 0));

        }

        (*f)(*this);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Renderer::render() {
    camera->updateWorldMatrix();
    scene->updateWorldMatrix();
    scene->traverse(camera);
}

void Renderer::terminate() {
    glfwTerminate();
}

void Renderer::resize() {
    int newWidth, newHeight;
    glfwGetFramebufferSize(window, &newWidth, &newHeight);

    if (newWidth != width || newHeight != height) {
        glViewport(0, 0, newWidth, newHeight);

        width = newWidth;
        height = newHeight;

        camera->aspect = (float) width / height;
        camera->updateProjectionMatrix();
    }
}

}
