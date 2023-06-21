#include <falcon/render/window.h>

namespace falcon {

RenderWindow::RenderWindow(GLFWwindow* window) : window(window) {
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
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

}
