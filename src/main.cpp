#include <exception>
#include <iostream>
#include <vector>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <poly/renderer.h>
#include <poly/program.h>

void loop(poly::Program program, unsigned int VAO);
void handleResize(GLFWwindow* window, int width, int height);

int main() {
    try {
        auto renderer = new poly::Renderer(1280, 720);
        glfwSetFramebufferSizeCallback(renderer->window, handleResize);

        auto program = poly::Program("./src/pbr.vs", "./src/pbr.fs");

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        unsigned int VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        renderer->run(loop, program, VAO);

        renderer->terminate();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}

void loop(poly::Program program, unsigned int VAO) {
    program.use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void handleResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
