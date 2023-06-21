#include <falcon/render/window.h>
#include <falcon/core/renderer.h>
#include <falcon/controls/orbit_controls.h>

namespace falcon {

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    static_cast<RenderWindow*>(glfwGetWindowUserPointer(window))->handleResize(width, height);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    static_cast<RenderWindow*>(glfwGetWindowUserPointer(window))->handleMouseButton(button, action);
}

void cursorPosCallback(GLFWwindow* window, double x, double y) {
    static_cast<RenderWindow*>(glfwGetWindowUserPointer(window))->handleMouseMove(x, y);
}

RenderWindow::RenderWindow(GLFWwindow* window) : window(window) {
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
};

RenderWindow::~RenderWindow() {
    glfwDestroyWindow(window);
}

void RenderWindow::getSize(int* width, int* height) {
    glfwGetFramebufferSize(window, width, height);
}

void RenderWindow::getCursor(double* x, double* y) {
    glfwGetCursorPos(window, x, y);
}

void RenderWindow::setRenderer(Renderer* renderer) {
    attachments.renderer = renderer;
}

void RenderWindow::setOrbitControls(OrbitControls* controls) {
    attachments.controls = controls;
}

void RenderWindow::handleResize(int width, int height) {
    if (attachments.renderer != nullptr) {
        attachments.renderer->handleResize(width, height);
    }

    if (attachments.controls != nullptr) {
        attachments.controls->handleResize(width, height);
    }
}

void RenderWindow::handleMouseButton(int button, int action) {
    if (attachments.controls != nullptr) {
        attachments.controls->handleMouseButton(button, action);
    }
}

void RenderWindow::handleMouseMove(double x, double y) {
    if (attachments.controls != nullptr) {
        attachments.controls->handleMouseMove(x, y);
    }
}

}
