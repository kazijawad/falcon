#ifndef renderer_h
#define renderer_h

#include <functional>
#include <memory>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <polyhedron/core/mesh.h>

namespace polyhedron {

class Renderer {
public:
    Renderer(unsigned int width, unsigned int height);
    ~Renderer();

    void setClearColor(float r, float g, float b, float a);

    void clearColor();
    void clearDepth();
    void clearStencil();
    void clear(bool color = true, bool depth = true, bool stencil = true);

    void run(std::function<void()> fn);

    void render(
        std::shared_ptr<Transform> scene,
        std::shared_ptr<Camera> camera
    );

    void terminate();

private:
    GLFWwindow* window;
    unsigned int width;
    unsigned int height;

    bool resize();
    std::vector<std::shared_ptr<Mesh>> getRenderList(
        std::shared_ptr<Transform> scene,
        std::shared_ptr<Camera> camera
    );
};

}

#endif
